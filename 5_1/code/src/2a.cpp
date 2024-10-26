#include <array>
#include <bitset>
#include <exception>
#include <iostream>

void bit_array_sort(std::array<int, 8>& arr, int& n);

int main(void) {
    using std::array, std::bitset;
    using std::cout, std::cin, std::endl;

    int n;
    std::array<int, 8> arr;

    cout << "Введите количество чисел (от 1 до 8 включительно): ";
    cin >> n;

    if (n < 1 || n > 8) throw std::exception();

    // ввод массива
    for (int i = 0; i < n; ++i) {
        cout << "Введите " << i + 1 << " число (число от 0 до 7 включительно): ";
        int temp;
        cin >> temp;
        if (temp < 0 || temp > 7) throw std::exception();
        arr.at(i) = temp;
    }

    cout << "до: ";
    for (int i = 0; i < n; ++i) {
        cout << arr.at(i) << ' ';
    }
    cout << endl;

    bit_array_sort(arr, n);

    cout << "после: ";
    for (int i = 0; i < n; ++i) {
        cout << arr.at(i) << ' ';
    }
    cout << endl;
}

void bit_array_sort(std::array<int, 8>& arr, int& n) {
    unsigned char bit_array = 0; // 8-битный битовый массив, состоящий из нулей

    // устанавливаем биты, соответствующие элементам массива
    for (int i = 0; i < n; ++i) {
        bit_array |= (unsigned char)1 << (unsigned char)arr.at(i);
    }

    int new_n = 0;
    // счетчиком i проходимся по битовому массиву
    // счетчиком j проходимся по исходному массиву
    for (int i = 0, j = 0; i < 8 && j < n; ++i) {
        // если бит установлен, то записать число i в исходный массив
        if (bit_array & ((unsigned char)1 << (unsigned char)i)) {
            arr[j++] = i;
            new_n++;
        }
    }

    // меняем значение n, чтобы в случае повтора элементов в исходном массиве
    // выводились только уникальные элементы и сортировка работала правильно
    n = new_n;
}
