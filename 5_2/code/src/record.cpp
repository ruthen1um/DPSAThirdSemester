#include <iostream>

#include "record.hpp"

Record::Record(int license_number, std::string business_name, std::string founder_name) {
    this->license_number = license_number;
    this->business_name = business_name;
    this->founder_name = founder_name;
}

void Record::print() {
    std::cout << "Номер лицензии: " << this->license_number << '\n';
    std::cout << "Название предприятия: " << this->business_name << '\n';
    std::cout << "Имя учредителя: " << this->founder_name << '\n';
}
