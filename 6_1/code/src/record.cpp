#include <iostream>

#include "record.hpp"

Record::Record(int product_code, std::string product_name, int product_price) {
    this->product_code = product_code;
    this->product_name = product_name;
    this->product_price = product_price;
}

void Record::display() const {
    std::cout << "Код продукта: " << this->product_code << '\n';
    std::cout << "Название продукта: " << this->product_name << '\n';
    std::cout << "Цена продукта: " << this->product_price << '\n';
}
