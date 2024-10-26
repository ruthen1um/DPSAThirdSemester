#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>

// структура записи
struct Record {
    int license_number;
    std::string business_name;
    std::string founder_name;

    Record(int license_number, std::string business_name, std::string founder_name);
    void print();
};

#endif
