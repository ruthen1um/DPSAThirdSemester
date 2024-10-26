#include <iostream>
#include <string>
#include <vector>
#include "record.hpp"
#include "1.hpp"

int main(void) {
    std::cout << "Введите число записей для генерации: ";
    int n;
    std::cin >> n;

    std::cout << "Введите имя файла (без расширения): ";
    std::string filename;
    std::cin >> filename;

    std::vector<Record> records;

    std::string text_file = filename + std::to_string(n) + ".csv";
    std::string binary_file = filename + std::to_string(n) + ".bin";

    generate_records(records, n);

    write_records_to_csv(records, text_file.c_str());
    write_records_to_bin(records, binary_file.c_str());
}
