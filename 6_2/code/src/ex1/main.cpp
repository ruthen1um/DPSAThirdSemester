#include <iostream>
#include <vector>
#include <string>

static std::vector<std::string> cpp_keywords {
    "signed", "const", "register", "default",
    "case", "auto", "char", "break",
    "continue", "void", "enum", "do",
    "else", "short", "extern", "for",
    "union", "int", "return", "switch",
    "static", "goto", "sizeof", "if",
    "struct", "float", "long", "double",
    "typedef", "unsigned", "volatile", "while"
};

void print_vector(std::vector<std::string>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it;
        if (it != v.end() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

void rearrange_strings(std::vector<std::string>& v) {
    bool swapped = false;

    for (int i = 0; i < v.size() - 1; ++i) {
        for (int j = 0; j < v.size() - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                swapped = true;
                std::swap(v[j], v[j + 1]);
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main(void) {
    std::cout << "До" << '\n';
    std::cout << std::string(20, '-') << '\n';
    print_vector(cpp_keywords);

    std::cout << '\n';
    rearrange_strings(cpp_keywords);

    std::cout << "После" << '\n';
    std::cout << std::string(20, '-') << '\n';
    print_vector(cpp_keywords);
}
