#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>
#include <vector>
#include "record.hpp"

std::string generate_string(int min, int max);
int generate_number(int min, int max);

int generate_product_code();
std::string generate_product_name();
int generate_product_price();

Record generate_record();
void generate_records(std::vector<Record>& records, const int n);

#endif
