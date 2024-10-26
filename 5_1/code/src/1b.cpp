#include <array>
#include <bitset>
#include <iostream>

void set_bit(unsigned char& x, unsigned char bit);

int main(void) {
    using std::array, std::bitset;
    using std::cout, std::cin, std::endl;

    array<unsigned char, 3> arr {219, 63, 10}; // массив с тестовыми числами

    for (auto& el : arr) {
        cout << "до: " << bitset<8>{el} << " = " << (unsigned int)el << endl;
        set_bit(el, 7); // устанавливаем 7 бит в 1
        cout << "после: " << bitset<8>{el} << " = " << (unsigned int)el << endl;
    }
}

void set_bit(unsigned char& x, unsigned char bit) {
    if (bit < 1|| bit > 8) return; // если число битов больше 8 или меньше 1, выйти из функции
    unsigned char mask = 1 << (bit - 1); // маска состоит из нулей и одной единицы, которая находится на позиции искомого бита
    x |= mask;
}
