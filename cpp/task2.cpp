

#include "task2.h"
#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

void task2(int argc, char* argv[]) {
    setlocale(0, "");
    
    std::string filename = "data.txt";
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--file" && i + 1 < argc) {
            filename = argv[i + 1];
            break;
        }
    }

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << "\n";
        return;
    }

    StringHashSet mySet(100);
    
    std::string command;
    std::string value;

    std::cout << "--- Начало обработки файла " << filename << " ---\n";

    while (infile >> command >> value) {
        if (command == "SETADD") {
            mySet.add(value);
            std::cout << "Добавлено: " << value << "\n";
        } 
        else if (command == "SETDEL") {
            mySet.remove(value);
            std::cout << "Удалено: " << value << "\n";
        } 
        else if (command == "SET_AT") {
            bool exists = mySet.contains(value);
            std::cout << "Проверка " << value << ": " << (exists ? "есть" : "нет") << "\n";
        }
    }
    
    infile.close();
    std::cout << "--- Обработка завершена ---\n";
}