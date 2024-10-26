#include <optional>
#include <fstream>

#include "record.hpp"
#include "3.hpp"

// функция для создания таблицы вида ключ - смещение
void generate_offset_table(Table& table, std::string filepath) {
    std::ifstream file {filepath};

    int offset = 0;

    while (true) {
        int license_number;
        char business_name_length;
        char founder_name_length;

        file.read(reinterpret_cast<char*>(&license_number), sizeof(license_number));

        file.read(reinterpret_cast<char*>(&business_name_length), sizeof(business_name_length));
        file.ignore(business_name_length);

        file.read(reinterpret_cast<char*>(&founder_name_length), sizeof(founder_name_length));
        file.ignore(founder_name_length);

        if (file.eof()) break;

        table.push_back(std::make_pair(license_number, offset));
        offset += sizeof(license_number) + sizeof(business_name_length) + business_name_length + sizeof(founder_name_length) + founder_name_length;
    }

}

// функция, которая возвращает смещение, соответствующее ключу
std::optional<int> get_offset_by_key(Table& offset_table, int key) {
    int start = 0;
    int end = offset_table.size() - 1;

    while (start < end) {
        auto mid = (start + end) / 2;

        auto offset_table_key = offset_table[mid].first;
        auto offset_table_value = offset_table[mid].second;

        if (offset_table_key == key) {
            return std::make_optional(offset_table_value);
        }

        if (key < offset_table_key) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return std::nullopt;
}

// функция для получения записи по смещению
std::optional<Record> get_record_by_offset(std::string filepath, int offset) {
    std::ifstream file {filepath};
    // учитываем смещение
    file.ignore(offset);

    int license_number;
    // считываем номер лицензии
    file.read(reinterpret_cast<char*>(&license_number), sizeof(license_number));

    char business_name_length;
    // считываем длину
    file.read(reinterpret_cast<char*>(&business_name_length), sizeof(business_name_length));

    std::string business_name;
    // резервируем место в строке
    business_name.resize(business_name_length);
    // считываем название предприятия
    file.read(business_name.data(), business_name_length);

    char founder_name_length;
    // считываем длину
    file.read(reinterpret_cast<char*>(&founder_name_length), sizeof(founder_name_length));

    std::string founder_name;
    // резервируем место в строке
    founder_name.resize(founder_name_length);
    // считываем имя учредителя
    file.read(founder_name.data(), founder_name_length);

    file.close();
    return std::make_optional(Record(license_number, business_name, founder_name));
}

std::optional<Record> binary_search(std::string filepath, Table& offset_table, int key) {
    return get_offset_by_key(offset_table, key)
        .and_then([filepath](int offset){ return get_record_by_offset(filepath, offset);});
}
