#include "task7.h"
#include "structures.h"  
#include <iostream>
#include <string>
#include <climits>

// ключ, значение и время последнего использования
struct CacheItem {
    int key;
    int value;
    int last_used;  // чем больше число, тем свежее элемент
    bool is_valid;  // занятость ячейки
};


int findInCache(Array<CacheItem>& cache, int capacity, int key, int& time_counter) {
    for (int i = 0; i < capacity; i++) {
        if (cache.data[i].is_valid && cache.data[i].key == key) {
            // Нашли
            time_counter++;
            cache.data[i].last_used = time_counter;
            return i;
        }
    }
    return -1; // не нашли
}

// положить ключ-значение в кэш
void cacheSet(Array<CacheItem>& cache, int capacity, int key, int value, int& time_counter) {
    // есть ли уже такой ключ
    int idx = findInCache(cache, capacity, key, time_counter);
    if (idx != -1) {
        // ключ уже есть просто обновляем значение
        cache.data[idx].value = value;
        return;
    }
    
    // ключа нет ищем место для нового элемента
    int oldest_idx = -1;      // индекс самой старой ячейки
    int min_time = INT_MAX;   // минимальное last_used
    bool has_empty = false;   // есть ли пустая ячейка
    
    for (int i = 0; i < capacity; i++) {
        if (!cache.data[i].is_valid) {
            // Нашли пустую ячейку — берём её
            oldest_idx = i;
            has_empty = true;
            break;
        }
        // Ищем самую старую занятую ячейку
        if (cache.data[i].last_used < min_time) {
            min_time = cache.data[i].last_used;
            oldest_idx = i;
        }
    }
    
    // Кладём новый элемент (в пустую ячейку или вместо самой старой)
    time_counter++;
    cache.data[oldest_idx] = {key, value, time_counter, true};
}

// Функция GET: получить значение по ключу
int cacheGet(Array<CacheItem>& cache, int capacity, int key, int& time_counter) {
    int idx = findInCache(cache, capacity, key, time_counter);
    if (idx != -1) {
        return cache.data[idx].value; // вернули значение
    }
    return -1; // ключа нет в кэше
}

void task7() {
    setlocale(0, "");
    
    std::cout << "=== Задание 7: LRU Кэш ===\n\n";
    
    // ёмкость кэша
    int cap;
    std::cout << "Введите ёмкость кэша: ";
    std::cin >> cap;
    
    if (cap <= 0) {
        std::cout << "Ошибка: ёмкость должна быть > 0\n";
        return;
    }
    
    int q;
    std::cout << "Введите количество запросов: ";
    std::cin >> q;
    
    Array<CacheItem> cache;
    cache.Init();
    
    for (int i = 0; i < cap; i++) {
        CacheItem empty = {0, 0, 0, false}; // пустая ячейка
        cache.MPush(empty);
    }
    
    int time_counter = 0; 
    
    std::cout << "\nРезультаты запросов:\n";
    
    // Обрабатываем запросы
    for (int i = 0; i < q; i++) {
        std::string command;
        std::cin >> command;
        std::cout << std::endl;
        
        std::cout << std::endl;

        if (command == "SET") {
            int key, value;
            std::cin >> key >> value;
            cacheSet(cache, cap, key, value, time_counter);
            std::cout << "SET " << key << " " << value << " → OK\n";
        } 
        else if (command == "GET") {
            int key;
            std::cin >> key;
            int result = cacheGet(cache, cap, key, time_counter);
            std::cout << "GET " << key << " → " << result << "\n";
        } 
        else {
            std::cout << "Неизвестная команда: " << command << "\n";
        }
    }
    
    cache.clear(); 
}