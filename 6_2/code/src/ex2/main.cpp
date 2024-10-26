#include <chrono>
#include <iostream>
#include <string>
#include "bmh.hpp"

int count_occurences_builtin(const std::string& str, const std::string& sub) {
    if (sub.length() == 0) return 0;
    int count = 0;

    size_t offset = str.find(sub);
    while (offset != std::string::npos) {
        offset = str.find(sub, offset + sub.length());
        count++;
    }

    return count;
}


int main(int argc, const char* argv[]) {
    std::cout << "Введите строку: ";
    std::string input_string;
    std::getline(std::cin, input_string);

    std::cout << "Введите образец: ";
    std::string pattern;
    std::getline(std::cin, pattern);

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    auto t1 = high_resolution_clock::now();
    auto count = bmh::count_occurences(input_string, pattern);
    auto t2 = high_resolution_clock::now();

    auto ns = duration_cast<nanoseconds>(t2 - t1);

    std::cout << "Число совпадений: " << count << std::endl;
    std::cout << "Число совпадений (с помощью встроенного метода): " << count_occurences_builtin(input_string, pattern) << std::endl;
    std::cout << "Время выполнения: " << ns.count() << " ns" << std::endl;
}
