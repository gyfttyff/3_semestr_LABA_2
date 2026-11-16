#pragma once

// для целых чисел с линейным пробированием
struct HashSet {
    int* table;       // храним сами числа
    int* state;       // массив состояний: 0 = пусто, 1 = занято, 2 = удалено
    int capacity;     

    // конструктор 
    HashSet(int cap);
    // деструктор 
    ~HashSet();
    
    // хеш-функция превращает число в индекс ящика
    int hash(int key);
    
    void add(int key);        // SETADD
    bool contains(int key);   // SET_AT
    void remove(int);         // SETDEL
};

struct StringHashSet {
    std::string* table; 
    int* state;        
    int capacity;       

    StringHashSet(int cap);
    ~StringHashSet();
    int hash(const std::string& key);
    void add(const std::string& key);
    bool contains(const std::string& key);
    void remove(const std::string& key);
};

// хеш-таблица с двойным хешированием 
struct DoubleHash {
    std::string* table;
    int* state;
    int capacity;

    DoubleHash(int cap);
    ~DoubleHash();
    int hash1(const std::string& key); // стартовый индекс 
    int hash2(const std::string& key); // шаг 
    void insert(const std::string& key);
    bool contains(const std::string& key);
};

// для хранения рёбер графа 
struct GraphHash {
    struct Edge {
        std::string from; // откуда 
        std::string to; // куда
        int weight; // вес (задержка)
        bool occupied; // занята ли ячейка
    };
    Edge* table;
    int capacity;

    GraphHash(int cap);
    ~GraphHash();
    int hash(const std::string& key);
    void addEdge(const std::string& from, const std::string& to, int weight);
    int getWeight(const std::string& from, const std::string& to);
};