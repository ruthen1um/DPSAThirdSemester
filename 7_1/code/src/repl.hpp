#ifndef REPL_HPP
#define REPL_HPP

#include <string>
#include "avl_tree.hpp"

void repl();

static void display_action_name(const std::string& str);
static void display_action_result(const std::string& str);

void repl_insert(AVLTree<std::string>& tree);
void repl_write_to_dot(AVLTree<std::string>& tree);
void repl_inorder(AVLTree<std::string>& tree);
void repl_postorder(AVLTree<std::string>& tree);
void repl_concat(AVLTree<std::string>& tree);
void repl_maxchar(AVLTree<std::string>& tree);
void repl_help(AVLTree<std::string>& tree);
void repl_exit(AVLTree<std::string>& tree);

#endif // REPL_HPP
