#include <unordered_map>
#include <iostream>
#include <string>
#include "dot.hpp"
#include "repl.hpp"
#include "avl_tree.hpp"
#include "avl_tree_functions.hpp"

using repl_command = void (*) (AVLTree<std::string>& tree);

static std::string helpstr = \
    "insert        добавить узел в дерево\n" \
    "write         записать в формат dot\n" \
    "inorder       выполнить симметричный обход по дереву\n" \
    "postorder     выполнить обратный обход по дереву\n" \
    "concat        вывести результат конкатенации всех листьев\n" \
    "maxchar       вывести самый часто встречающийся символ\n" \
    "help          вывести список доступных команд с пояснениями\n" \
    "exit          завершить работу программы\n";

static std::unordered_map<std::string, repl_command> commands = {
    { "insert",     &repl_insert       },
    { "write",      &repl_write_to_dot },
    { "inorder",    &repl_inorder      },
    { "postorder",  &repl_postorder    },
    { "concat",     &repl_concat       },
    { "maxchar",    &repl_maxchar      },
    { "help",       &repl_help         },
    { "exit",       &repl_exit         },
};

static void display_action_name(const std::string& str) {
    std::cout << "--- " << str << " ---" << std::endl;
}

static void display_action_result(const std::string& str) {
    std::cout << " * " << str << std::endl;
}

void repl_insert(AVLTree<std::string>& tree) {
    display_action_name("Добавление узла в дерево");

    std::cout << "Введите значение узла: " << std::flush;
    std::string value;
    std::cin >> value;

    std::cin.ignore();

    tree.insert(value);
}

void repl_write_to_dot(AVLTree<std::string>& tree) {
    display_action_name("Запись в формат dot");
    write_to_dot("tree.dot", tree);
}

void repl_inorder(AVLTree<std::string>& tree) {
    display_action_name("Симметричный обход дерева");
    tree.traverse_inorder();
}

void repl_postorder(AVLTree<std::string>& tree) {
    display_action_name("Обратный обход дерева");
    tree.traverse_postorder();
}

void repl_concat(AVLTree<std::string>& tree) {
    display_action_name("Конкатенация значений всех листьев дерева");
    std::cout << concatenate_leaves(tree) << std::endl;
}

void repl_maxchar(AVLTree<std::string>& tree) {
    display_action_name("Вывод самого частого символа среди значений всех узлов дерева");
    std::cout << get_most_occuring_char(tree) << std::endl;
}

void repl_help(AVLTree<std::string>& tree) {
    display_action_name("Список команд");
    std::cout << helpstr;
}

void repl_exit(AVLTree<std::string>& tree) {
    display_action_name("Выход");
}

void repl() {
    AVLTree<std::string> tree;
    std::cout << "Добро пожаловать! Введите команду help, чтобы увидеть список доступных команд." << std::endl;

    while (true) {
        std::cout << "> ";

        std::string command;
        std::getline(std::cin, command);

        if (command == "exit") {
            commands.at("exit")(tree);
            break;
        } else if (commands.contains(command)) {
            commands.at(command)(tree);
        } else {
            std::cout << "Неверная команда. Введите команду help, чтобы увидеть список доступных команд." << std::endl;
        }
    }

}
