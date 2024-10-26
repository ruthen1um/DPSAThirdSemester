#ifndef REPL_HPP
#define REPL_HPP

#include <string>
#include "hashset.hpp"

void repl();

static bool is_digits(const std::string& str);

static decltype(Record::product_code) get_product_code();
static decltype(Record::product_name) get_product_name();
static decltype(Record::product_price) get_product_price();

static void display_action_name(const std::string& str);
static void display_action_result(const std::string& str);

void repl_display(custom::HashSet& hashset);
void repl_insert(custom::HashSet& hashset);
void repl_remove(custom::HashSet& hashset);
void repl_find(custom::HashSet& hashset);
void repl_fill(custom::HashSet& hashset);
void repl_help(custom::HashSet& hashset);
void repl_exit(custom::HashSet& hashset);

#endif
