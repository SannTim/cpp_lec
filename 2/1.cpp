#include <vector>
#include <iostream>

int main() {
    std::vector<bool> v = {true, false, true};
    
    // Компилируется
    for (auto&& x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Ошибка компиляции
    for (auto& x : v) {
        std::cout << x << " "; // Компилятор выдаст ошибку
    }
    return 0;
}

