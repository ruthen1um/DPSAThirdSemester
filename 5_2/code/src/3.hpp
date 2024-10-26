#ifndef _3_HPP
#define _3_HPP

#include <vector>
#include <optional>

#include "record.hpp"

using Table = std::vector<std::pair<int, int>>;

void generate_offset_table(Table& table, std::string filepath);
std::optional<int> get_offset_by_key(Table& offset_table, int key);
std::optional<Record> get_record_by_offset(std::string filepath, int offset);
std::optional<Record> binary_search(std::string filepath, Table& offset_table, int key);

#endif
