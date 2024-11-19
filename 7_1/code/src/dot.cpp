#include <fstream>
#include <sstream>
#include <stdexcept>
#include "dot.hpp"

void write_to_dot(const char* filepath, AVLTree<std::string>& tree) {
    std::ofstream file {filepath};

    if (file.bad()) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    std::stringstream oss;
    oss << "digraph main {" << std::endl;
    oss << "node [shape=circle]" << std::endl;

    auto it = AVLTreeInOrderIterator<std::string>(tree);

    while (it.has_next()) {
        auto node = it.next();
        if (node->left) {
            oss << node->value << " -> " << node->left->value << std::endl;
        }
        if (node->right) {
            oss << node->value << " -> " << node->right->value << std::endl;
        }
    }

    oss << '}' << std::endl;

    file << oss.rdbuf();

    file.close();
}
