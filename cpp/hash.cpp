#include "hash.h"

// конструктор
HashSet::HashSet(int cap) {
    capacity = cap;
    table = new int[capacity];
    state = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        state[i] = 0; // изначально все ящики пустые 
    }
}

// деструктор
HashSet::~HashSet() {
    delete[] table;
    delete[] state;
}

// хеш-функция 
int HashSet::hash(int key) {
    // + capacity нужен для корректной работы с отрицательными числами в C++
    return (key % capacity + capacity) % capacity;
}

// добавление элемента 
void HashSet::add(int key) {
    int idx = hash(key); // Считаем стартовый ящик
    
    // ищем свободный ящик или такой, где уже лежит этот же ключ
    while (state[idx] == 1) { // 1 - занято
        if (table[idx] == key) {
            return; // если уже есть - выходим
        }
        idx = (idx + 1) % capacity; // линейное пробирование идём к следующему ящику
    }
    
    // нашли свободный или удалённый
    table[idx] = key;
    state[idx] = 1; 
}
// проверка наличия 
bool HashSet::contains(int key) {
    int idx = hash(key);
    int startIdx = idx; // запоминаем начало, чтобы не ходить по кругу вечно
    
    while (state[idx] != 0) { 
        if (state[idx] == 1 && table[idx] == key) {
            return true; // нашли
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx) break; // прошли полный круг и не нашли
    }
    return false;
}

// удаление элемента 
void HashSet::remove(int key) {
    int idx = hash(key);
    int startIdx = idx;
    
    while (state[idx] != 0) {
        if (state[idx] == 1 && table[idx] == key) {
            state[idx] = 2; // помечаем как удалено 
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx) break;
    }
}


StringHashSet::StringHashSet(int cap) {
    capacity = cap;
    table = new std::string[capacity];
    state = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        state[i] = 0; // Все ячейки пустые
    }
}

StringHashSet::~StringHashSet() {
    delete[] table;
    delete[] state;
}

// хеш-функция для строк суммируем коды символов
int StringHashSet::hash(const std::string& key) {
    unsigned long h = 0;
    for (char c : key) {
        h = (h * 31 + c); // 31 простое число, хорошо распределяет хеши
    }
    return (h % capacity + capacity) % capacity;
}

void StringHashSet::add(const std::string& key) {
    int idx = hash(key);
    while (state[idx] == 1) {
        if (table[idx] == key) {
            return; // Уже есть, дубликаты не нужны
        }
        idx = (idx + 1) % capacity; // Линейное пробирование
    }
    table[idx] = key;
    state[idx] = 1;
}

bool StringHashSet::contains(const std::string& key) {
    int idx = hash(key);
    int startIdx = idx;
    while (state[idx] != 0) {
        if (state[idx] == 1 && table[idx] == key) {
            return true;
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx) break;
    }
    return false;
}

void StringHashSet::remove(const std::string& key) {
    int idx = hash(key);
    int startIdx = idx;
    while (state[idx] != 0) {
        if (state[idx] == 1 && table[idx] == key) {
            state[idx] = 2; // Помечаем как удаленное
            return;
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx) break;
    }
}

// двойное хэширование

DoubleHash::DoubleHash(int cap) {
    capacity = cap;
    table = new std::string[capacity];
    state = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        state[i] = 0;
    }
}

DoubleHash::~DoubleHash() {
    delete[] table;
    delete[] state;
}

// Первая хеш-функция
int DoubleHash::hash1(const std::string& key) {
    unsigned long h = 0;
    for (char c : key) {
        h = (h * 31 + c);
    }
    return h % capacity;
}

// Вторая хеш-функция (для двойного хеширования)
int DoubleHash::hash2(const std::string& key) {
    unsigned long h = 0;
    for (char c : key) {
        h = (h * 37 + c); // 37 — другое простое число
    }
    return (h % (capacity - 1)) + 1; // шаг от 1 до capacity-1
}

void DoubleHash::insert(const std::string& key) {
    int idx = hash1(key);
    int step = hash2(key);
    
    while (state[idx] == 1) {
        if (table[idx] == key) return;
        idx = (idx + step) % capacity; // двойное хеширование
    }
    table[idx] = key;
    state[idx] = 1;
}

bool DoubleHash::contains(const std::string& key) {
    int idx = hash1(key);
    int step = hash2(key);
    int startIdx = idx;
    
    while (state[idx] != 0) {
        if (state[idx] == 1 && table[idx] == key) return true;
        idx = (idx + step) % capacity;
        if (idx == startIdx) break;
    }
    return false;
}

// GraphHash 

GraphHash::GraphHash(int cap) {
    capacity = cap;
    table = new Edge[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i].occupied = false;
    }
}

GraphHash::~GraphHash() {
    delete[] table;
}

int GraphHash::hash(const std::string& key) {
    unsigned long h = 0;
    for (char c : key) {
        h = (h * 31 + c);
    }
    return h % capacity;
}

void GraphHash::addEdge(const std::string& from, const std::string& to, int weight) {
    std::string key = from + "->" + to;
    int idx = hash(key);
    
    while (table[idx].occupied) {
        if (table[idx].from == from && table[idx].to == to) {
            table[idx].weight = weight; // обновляем вес
            return;
        }
        idx = (idx + 1) % capacity;
    }
    table[idx].from = from;
    table[idx].to = to;
    table[idx].weight = weight;
    table[idx].occupied = true;
}

int GraphHash::getWeight(const std::string& from, const std::string& to) {
    std::string key = from + "->" + to;
    int idx = hash(key);
    int start = idx;
    
    while (table[idx].occupied) {
        if (table[idx].from == from && table[idx].to == to) {
            return table[idx].weight;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
    return -1; // ребро не найдено
}
