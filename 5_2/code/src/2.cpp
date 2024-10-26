#include <fstream>
#include <optional>
#include <string>

#include "record.hpp"
#include "2.hpp"

// функция для нахождения записи по ключу в бинарном файле
std::optional<Record> linear_search(std::string filepath, int key) {
    std::ifstream file {filepath};

    while (!file.eof()) {
        int license_number;
        char business_name_length;
        char founder_name_length;

        file.read(reinterpret_cast<char*>(&license_number), sizeof(license_number));

        // если ключ найден, вернуть запись
        if (license_number == key) {
            std::string business_name;
            std::string founder_name;

            // считываем длину
            file.read(reinterpret_cast<char*>(&business_name_length), sizeof(business_name_length));
            // резервируем место в строке
            business_name.resize(business_name_length);
            // считываем название предприятия
            file.read(business_name.data(), business_name_length);

            // считываем длину
            file.read(reinterpret_cast<char*>(&founder_name_length), sizeof(founder_name_length));
            // резервируем место в строке
            founder_name.resize(founder_name_length);
            // считываем имя учредителя
            file.read(founder_name.data(), founder_name_length);

            file.close();
            return std::make_optional(Record(license_number, business_name, founder_name));
        } else {
            file.read(reinterpret_cast<char*>(&business_name_length), sizeof(business_name_length));
            file.ignore(business_name_length);

            file.read(reinterpret_cast<char*>(&founder_name_length), sizeof(founder_name_length));
            file.ignore(founder_name_length);
        }
    }

    file.close();
    return std::nullopt;
}
