#include <filesystem>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <numeric>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>

void generate_numbers(const char *filepath, int start, int end);
void bit_array_sort_file(const char *filepath, int start, int end);

int main(void) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    const int start_number = 1;
    const int end_number = 1024 * 1024 * 4; // размер битового массива в памяти - 0.5 Мб

    auto source_file_path = "src.txt";
    auto copied_file_path = "numbers.txt";

    generate_numbers(source_file_path, start_number, end_number);

    // копируем файл, чтобы не перезаписать исходный
    std::filesystem::copy_file(source_file_path, copied_file_path, std::filesystem::copy_options::overwrite_existing);

    auto t1 = high_resolution_clock::now();

    bit_array_sort_file(copied_file_path, start_number, end_number);

    auto t2 = high_resolution_clock::now();

    auto ms = duration_cast<milliseconds>(t2 - t1);

    std::cout << "Время выполнения: " << ms.count() << " мс" << std::endl;

    // добавленная строка кода
    std::cout << "Объем используемой памяти: " << (double)(end_number - start_number + 1) / (double)(8 * 1024 * 1024) << " Мб" << std::endl;
}

void generate_numbers(const char *filepath, int start, int end) {
    std::fstream file;

    file.open(filepath, std::fstream::out | std::fstream::trunc);

    const int n = end - start + 1;

    auto random_engine = std::default_random_engine();
    random_engine.seed(std::chrono::system_clock::now()
                       .time_since_epoch()
                       .count());

    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), start);
    std::shuffle(v.begin(), v.end(), random_engine);

    for (const auto& el : v) {
        file << el << '\n';
    }

    file.close();
}

void bit_array_sort_file(const char *filepath, int start, int end) {
    std::fstream file;

    const int n = end - start + 1;
    std::vector<bool> bit_array(n);

    file.open(filepath, std::fstream::in);

    // устанавливаем биты, соответствующие элементам массива, записанного в файл
    for (int i = 0; i < n; ++i) {
        int temp;
        file >> temp;
        if (temp < start || temp > end) {
            throw std::runtime_error("число заходит за границы отрезка [start;end]");
        }
        bit_array[end - temp] = 1;
    }

    file.close();

    file.open(filepath, std::fstream::out | std::fstream::trunc);

    for (int i = 0; i < n; ++i) {
        // если бит установлен, то записать соответствующее число в файл
        if (bit_array[n - 1 - i]) {
            file << i + start << '\n';
        }
    }

    file.close();
}
