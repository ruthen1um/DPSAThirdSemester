#include <unordered_set>
#include <random>
#include <string>
#include "generator.hpp"
#include "record.hpp"

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

int generate_product_code() {
    return generate_number(100000, 999999);
}

std::string generate_product_name() {
    return generate_string(5, 15);
}

int generate_product_price() {
    return generate_number(1000, 1000000);
}

// генератор записи
Record generate_record() {
    return Record(
        generate_product_code(),
        generate_product_name(),
        generate_product_price()
    );
}

// генератор записей (без повторов ключей)
void generate_records(std::vector<Record>& records, const int n) {
    std::unordered_set<int> product_codes;

    while (product_codes.size() < n) {
        auto record = generate_record();

        // если такой ключ уже существует, то нужно перегенерировать запись
        if (product_codes.contains(record.product_code) != 0) {
            continue;
        }

        product_codes.insert(record.product_code);
        records.push_back(record);
    }
}
