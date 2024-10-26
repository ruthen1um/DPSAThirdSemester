#include <string>
#include "bmh.hpp"
#include "hashset.hpp"

namespace bmh {

int count_occurences(std::string str, std::string pattern) {
    int occurences = 0;

    int n = str.length();
    int m = pattern.length();

    custom::HashSet<char, int> shifts;

    for (int i = m - 2; i >= 0; --i) {
        shifts.insert({ pattern[i], m - i - 1 });
    }

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        // сравниваем посимвольно образец и часть строки
        while (j >= 0 && str[i + j] == pattern[j]) {
            j--;
        }

        // подстрока и образец совпали
        if (j < 0) {
            occurences++;
            i += m;
        } else {
            int stop_char = str[i + j];
            int shift = shifts.contains(stop_char) ? shifts.at(stop_char) : m;
            i += shift;
        }
    }

    return occurences;
}

} // namespace bmh
