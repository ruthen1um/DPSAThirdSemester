#ifndef _1_HPP
#define _1_HPP

#include <vector>
#include <string>

#include "record.hpp"

std::string generate_string(int min, int max);
int generate_number(int min, int max);
int generate_license_number();
std::string generate_business_name();
std::string generate_founder_name();
Record generate_record();
void generate_records(std::vector<Record>& records, const int n);
void write_records_to_csv(std::vector<Record>& records, std::string filepath);
void write_records_to_bin(std::vector<Record>& records, std::string filepath);

#endif
