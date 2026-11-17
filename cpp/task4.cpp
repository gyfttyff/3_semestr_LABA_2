#include "task4.h"
#include "structures.h"
#include <iostream>
#include <string>

void task4() {
    setlocale(0, "");
    
    int n;
    std::cout << "Введите количество элементов: ";
    if (!(std::cin >> n)) return;

    Array<std::string> arr;
    arr.Init();

    std::cout << "Введите элементы через пробел: ";
    for (int i = 0; i < n; ++i) {
        std::string val;
        std::cin >> val;
        arr.MPush(val); // добавляем элемент в массив
    }

    // total = 2 в степени n (количество всех возможных подмножеств)
    int total = 1 << n;
    
    std::cout << "Результат:\n";
    
    
    for (int i = 0; i < total; ++i) {
        std::cout << "{";
        bool first = true; 
        
        // проверяем каждый бит числа i
        for (int j = 0; j < n; ++j) {
            // (i >> j) сдвигает биты вправо на j позиций
            // & 1 проверяет, равен ли самый младший бит 1
            if ((i >> j) & 1) {
                if (!first) std::cout << ", ";
                std::cout << arr.data[j];
                first = false;
            }
        }
        std::cout << "} ";
    }
    std::cout << "\n";
    
    arr.clear();
}