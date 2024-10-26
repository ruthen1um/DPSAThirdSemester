#include <optional>
#include <iostream>
#include "hashset.hpp"
#include "record.hpp"

namespace custom {

using hash_type = HashSet::hash_type;
using key_type = HashSet::key_type;

std::size_t HashSet::size(void) const {
    return table.size();
}

void HashSet::rehash(void) {
    std::vector<Record> records;
    // копируем все записи
    for (const auto& option : table) {
        if (option.has_value()) {
            records.push_back(option.value());
        }
    }

    // очищаем вектор
    for (auto& record : table) {
        record = std::nullopt;
    }

    // вновь добавляем записи
    for (const auto& record : records) {
        insert(record);
    }
}

hash_type HashSet::get_hash(key_type key) {
    hash_type hash = 0;
    auto digit_sum = 0;

    while (key) {
        int digit = key % 10;
        digit_sum += digit;
        hash += digit * 3;
        key /= 10;
    }

    hash -= digit_sum;

    return hash;
}

hash_type HashSet::get_probe_hash(key_type key, int n) {
    auto old_hash = get_hash(key);
    return old_hash + 1 * n + 1 * n * n;
}

HashSet::HashSet(std::size_t size): table{} {
    elements_count = 0;
    resize(size);
}

void HashSet::resize(std::size_t size) {
    table.resize(size);
    rehash();
}

bool HashSet::insert(const Record& value) {
    // если коэффициент нагрузки больше или равен 0.75 - увеличить размер вдвое и рехешировать
    auto load_factor = static_cast<float>(elements_count) / static_cast<float>(table.size());
    if (load_factor >= 0.75) {
        resize(table.size() * 2);
    }

    auto key = value.product_code;

    // проверка на существование такого ключа
    auto option = find(key);
    if (option.has_value()) {
        return false;
    }

    auto index = get_hash(key) % table.size();
    /* индекс уже занят */
    if (table.at(index) != std::nullopt) {

        /* пробируем индексы, пока не был найден свободный индекс */
        int attempt = 1;
        while (true) {
            index = get_probe_hash(key, attempt);

            /* удвоить размер хеш-таблицы и рехешировать её,
            если индекс выходит за её границы */
            if (index >= table.size()) {
                resize(table.size() * 2);
                return insert(value);
            }

            /* выйти из цикла, если индекс - свободный */
            if (table.at(index) == std::nullopt) {
                break;
            }

            attempt++;
        }
    }

    table.at(index) = value;
    elements_count++;
    return true;
}

std::optional<Record> HashSet::find(key_type key) {
    auto index = get_hash(key) % table.size();
    const auto& option = table.at(index);

    if (option.has_value()) {
        if (key == option->product_code) {
            return option;
        }

        int attempt = 1;
        while (true) {
            index = get_probe_hash(key, attempt);
            if (index >= table.size()) break;
            if (key == table.at(index)->product_code) {
                return table.at(index);
            }
            attempt++;
        }
    }

    return std::nullopt;
}

bool HashSet::remove(key_type key) {
    auto index = get_hash(key) % table.size();
    auto& option = table.at(index);

    if (option.has_value()) {
        if (key == option->product_code) {
            option = std::nullopt;
            elements_count--;
            rehash();
            return true;
        }

        int attempt = 1;
        while (true) {
            index = get_probe_hash(key, attempt);
            if (index >= table.size()) {
                return false;
            }

            if (key == table.at(index)->product_code) {
                table.at(index) = std::nullopt;
                rehash();
                return true;
            }
            attempt++;
        }
    }
    return false;
}

void HashSet::display(void) {
    for (const auto& option : table) {
        if (option.has_value()) {
            option->display();
            std::cout << "--------------------" << std::endl;
        }
    }
}

} // namespace custom
