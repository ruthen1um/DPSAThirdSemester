#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>

// структура записи
struct Record {
    int product_code;
    std::string product_name;
    int product_price;

    Record(int product_code, std::string product_name, int product_price);
    void display() const;
};

#endif
