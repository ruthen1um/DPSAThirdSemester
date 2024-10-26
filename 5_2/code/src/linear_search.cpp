#include <iostream>
#include <chrono>
#include "2.hpp"

void measure_time(std::string filepath, int key) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto result = linear_search(filepath, key);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (result.has_value()) {
        auto record = result.value();
        record.print();
    } else {
        std::cout << "Запись не найдена" << std::endl;
    }

    std::cout << "Время работы: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;

}

int main(void) {
    std::string binary_file;
    std::cout << "Введите название бинарного файла: ";
    std::cin >> binary_file;

    int search_key;
    std::cout << "Введите ключ для поиска: ";
    std::cin >> search_key;
    std::cout << "------------------------" << std::endl;

    measure_time(binary_file, search_key);
}
