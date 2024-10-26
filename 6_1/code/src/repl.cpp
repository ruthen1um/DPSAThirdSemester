#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string>
#include "generator.hpp"
#include "hashset.hpp"
#include "repl.hpp"

using repl_command = void (*) (custom::HashSet& hashset);

static std::unordered_map<std::string, std::string> helplist = {
    { "display", "вывести на экран все записи в хеш-множестве"                },
    { "insert",  "вставить запись в хеш-множество"                            },
    { "remove",  "удалить запись из хеш-множества по ключу"                   },
    { "find",    "найти запись в хеш-множестве по ключу"                      },
    { "fill",    "заполнить хеш-множество случайно сгенерированными записями" },
    { "help",    "вывести список доступных команд с пояснениями"              },
    { "exit",    "завершить работу программы"                                 },
};

static std::unordered_map<std::string, repl_command> commands = {
    { "display", &repl_display },
    { "insert",  &repl_insert  },
    { "remove",  &repl_remove  },
    { "find",    &repl_find    },
    { "fill",    &repl_fill    },
    { "help",    &repl_help    },
    { "exit",    &repl_exit    },
};

static bool is_digits(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

static decltype(Record::product_code) get_product_code() {
    std::string product_code;
    std::getline(std::cin, product_code);

    while (true) {
        if (is_digits(product_code)) {
            auto tmp = std::stoi(product_code);
            if (100000 <= tmp && tmp <= 999999) {
                break;
            }
        }

        std::cout << "Ошибка ввода. Введите шестиразрядное число: ";
        std::getline(std::cin, product_code);
    }

    return std::stoi(product_code);
}

static decltype(Record::product_name) get_product_name() {
    std::string product_name;
    std::getline(std::cin, product_name);

    return product_name;
}

static decltype(Record::product_price) get_product_price() {
    std::string product_price;
    std::getline(std::cin, product_price);

    while (!is_digits(product_price)) {
        std::cout << "Ошибка ввода. Введите число: ";
        std::getline(std::cin, product_price);
    }

    return std::stoi(product_price);
}

static void display_action_name(const std::string& str) {
    std::cout << "--- " << str << " ---" << std::endl;
}

static void display_action_result(const std::string& str) {
    std::cout << " * " << str << std::endl;
}

void repl_display(custom::HashSet& hashset) {
    display_action_name("Вывод записей");
    hashset.display();
}

void repl_insert(custom::HashSet& hashset) {
    display_action_name("Добавление записи");

    std::cout << "Введите код продукта (шестиразрядное число): ";
    auto product_code = get_product_code();

    std::cout << "Введите название продукта (строка): ";
    auto product_name = get_product_name();

    std::cout << "Введите цену продукта (число): ";
    auto product_price = get_product_price();

    auto record = Record(product_code, product_name, product_price);
    auto record_inserted = hashset.insert(record);

    if (record_inserted) {
        display_action_result("Запись добавлена успешно.");
    } else {
        display_action_result("Не удалось добавить запись: ключ уже существует.");
    }
}

void repl_remove(custom::HashSet& hashset) {
    display_action_name("Удаление записи");

    std::cout << "Введите ключ, по которому будет удалёна запись: ";
    auto key = get_product_code();

    auto record_removed = hashset.remove(key);

    if (record_removed) {
        display_action_result("Запись удалена успешно.");
    } else {
        display_action_result("Не удалось удалить запись: запись не найдена.");
    }
}

void repl_find(custom::HashSet& hashset) {
    display_action_name("Поиск записи");

    std::cout << "Введите ключ, по которому будет найдена запись: ";
    auto key = get_product_code();

    auto option = hashset.find(key);
    auto record_found = option.has_value();

    if (record_found) {
        std::cout << "--------------------" << std::endl;
        option->display();
        std::cout << "--------------------" << std::endl;
        display_action_result("Запись найдена успешно.");
    } else {
        display_action_result("Запись не найдена.");
    }
}

void repl_fill(custom::HashSet& hashset) {
    display_action_name("Заполнение случайными записями");

    std::cout << "Введите число записей для генерации: ";
    std::string n_str;
    std::getline(std::cin, n_str);

    while (!is_digits(n_str)) {
        std::cout << "Ошибка ввода. Введите число: ";
        std::getline(std::cin, n_str);
    }

    int n = std::stoi(n_str);

    std::vector<Record> records;
    generate_records(records, n);
    for (const auto& record : records) {
        hashset.insert(record);
    }

    display_action_result("Записи успешно добавлены.");
}

void repl_help(custom::HashSet& hashset) {
    display_action_name("Список команд");
    for (const auto& [key, value] : helplist) {
        std::cout << key << "   " << value << std::endl;
    }
}

void repl_exit(custom::HashSet& hashset) {
    display_action_name("Выход");
}

void repl() {
    custom::HashSet hashset{10};
    std::cout << "Добро пожаловать! Введите команду help, чтобы увидеть список доступных команд." << std::endl;

    while (true) {
        std::cout << "> ";

        std::string command;
        std::getline(std::cin, command);

        if (command == "exit") {
            commands.at("exit")(hashset);
            break;
        } else if (commands.contains(command)) {
            commands.at(command)(hashset);
        } else {
            std::cout << "Неверная команда. Введите команду help, чтобы увидеть список доступных команд." << std::endl;
        }
    }

}
