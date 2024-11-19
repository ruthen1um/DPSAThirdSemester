#include <string>
#include <unordered_map>
#include "avl_tree_functions.hpp"
#include "avl_tree.hpp"

std::string concatenate_leaves(AVLTree<std::string>& tree) {
    std::string s;

    auto it = AVLTreeInOrderIterator<std::string>(tree);

    while (it.has_next()) {
        auto node = it.next();
        if (node->left == nullptr && node->right == nullptr) {
            s += node->value;
        }
    }

    return s;
}

char get_most_occuring_char(AVLTree<std::string>& tree) {
    std::unordered_map<char, std::size_t> m;
    std::string s;

    auto it = AVLTreeInOrderIterator<std::string>(tree);

    while (it.has_next()) {
        auto node = it.next();
        s += node->value;
    }

    for (const auto& c: s) {
        if (m.contains(c)) {
            m.at(c)++;
        } else {
            m.insert({ c, 1 });
        }
    }

    std::size_t max_count = 0;
    char max_char;
    for (const auto& [key, value]: m) {
        if (value > max_count) {
            max_char = key;
            max_count = value;
        }
    }

    return max_char;
}
