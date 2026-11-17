#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"

int main(int argc, char* argv[]) {
    setlocale(0, "");
    
    int choice;
    
    while (true) {
        
        std::cout << "1. Стек (инфиксная -> постфиксная)\n";
        std::cout << "2. АТД Множество (из файла)\n";
        std::cout << "3. Разбиение множества\n";
        std::cout << "4. Различные подмассивы\n";
        std::cout << "5. Развилки бинарного дерева\n";
        std::cout << "6. Оптимизация маршрутов (хеш-таблица)\n";
        std::cout << "7. LRU кэш\n";
        std::cout << "0. Выход\n";
        
        std::cout << "Выберите задачу: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        if (choice == 0) {
            std::cout << "Выход из программы.\n";
            break;
        }
        
        std::cout << "\n";
        
        switch (choice) {
            case 1: task1(); break;
            case 2: task2(argc, argv); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            default: std::cout << "Нет такой задачи!\n";
        }
        
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
    
    return 0;
}