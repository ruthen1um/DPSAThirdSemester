#include <unordered_set>
#include <fstream>
#include <random>
#include <string>

#include "record.hpp"
#include "1.hpp"

// генератор строк
std::string generate_string(int min, int max) {
    std::random_device rd;
    std::default_random_engine random_generator(rd());
    std::uniform_int_distribution<int> generate_length(min, max);

    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string res = "";

    std::uniform_int_distribution<int> generate_char(0, alphabet.size() - 1);

    int n = generate_length(random_generator);
    for (int i = 0; i < n; ++i) {
        res += alphabet[generate_char(random_generator)];
    }

    return res;
}

// генератор чисел
int generate_number(int min, int max) {
    std::random_device rd;
    std::default_random_engine random_generator(rd());
    std::uniform_int_distribution<int> generate(min, max);

    return generate(random_generator);
}

int generate_license_number() {
    return generate_number(1000000, 9999999);
}

std::string generate_business_name() {
    return generate_string(10, 30);
}

std::string generate_founder_name() {
    return generate_string(5, 10) + ' ' + generate_string(5, 10) + ' ' + generate_string(5, 10);
}

// генератор записи
Record generate_record() {
    return Record(
        generate_license_number(),
        generate_business_name(),
        generate_founder_name()
    );
}

// генератор записей (без повторов ключей)
void generate_records(std::vector<Record>& records, const int n) {
    std::unordered_set<int> license_numbers;

    while (license_numbers.size() < n) {
        auto record = generate_record();

        // если такой ключ уже существует, то нужно перегенерировать запись
        if (license_numbers.count(record.license_number) != 0) {
            continue;
        }

        license_numbers.insert(record.license_number);
        records.push_back(record);
    }
}

// запись в текстовый файл (csv)
void write_records_to_csv(std::vector<Record>& records, std::string filepath) {
    const std::string sep = ", ";
    std::ofstream file {filepath};

    for (const auto& record : records) {
        file << std::to_string(record.license_number) << sep << record.business_name << sep << record.founder_name << '\n';
    }

    file.close();
}

// запись в бинарный файл (bin)
void write_records_to_bin(std::vector<Record>& records, std::string filepath) {
    std::ofstream file {filepath};

    /*
    в бинарном виде запись имеет следующий вид:
    | номер лицензии (4 байта) | длина названия предприятия (1 байт) | название предприятия | длина имени учредителя (1 байт) | имя учредителя |
    */

    for (const auto& record : records) {
        file.write(reinterpret_cast<const char*>(&record.license_number), sizeof(record.license_number));

        char business_name_length = record.business_name.size();
        file.write(reinterpret_cast<const char*>(&business_name_length), sizeof(business_name_length));
        file.write(record.business_name.c_str(), business_name_length);

        char founder_name_length = record.founder_name.size();
        file.write(reinterpret_cast<const char*>(&founder_name_length), sizeof(founder_name_length));
        file.write(record.founder_name.c_str(), founder_name_length);
    }

    file.close();
}
