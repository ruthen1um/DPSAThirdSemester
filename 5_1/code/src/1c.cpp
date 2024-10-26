#include <bitset>
#include <cmath>
#include <iostream>

int main(void) {
    unsigned int x = 25; // 00000000 00000000 00000000 00011001
    const int n = sizeof(x) * 8; // 32 бита
    unsigned int mask = (1 << (n - 1)); // 10000000 00000000 00000000 00000000

    std::cout << "Начальный вид маски: " << std::bitset<n>{mask} << std::endl;
    std::cout << "Результат: ";

    for (int i = 1; i <= n; i++) {
        std::cout << ((x & mask) >> (n - i)); // вывод на экран n - i + 1 бита
        mask = mask >> 1; // установленный в маске бит двигается слева направо n раз
    }

    std::cout << std::endl;
}
