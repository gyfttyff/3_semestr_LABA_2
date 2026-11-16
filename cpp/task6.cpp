#include "task6.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <string>
#include <climits>

// упрощённый алгоритм Дейкстры для поиска кратчайшего пути
// graph - хеш таблица рёбер
// start - имя нач сервера
// end - имя конца
// nodes - список серверов
int dijkstra(GraphHash& graph, const std::string& start, const std::string& end, 
             const std::vector<std::string>& nodes) {
    
    std::vector<int> dist(nodes.size(), INT_MAX); // массив расстояний
    std::vector<bool> visited(nodes.size(), false); // массив посещений вершины
    
    // находим start и end
    int startIdx = -1, endIdx = -1;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] == start) startIdx = i;
        if (nodes[i] == end) endIdx = i;
    }
    
    if (startIdx == -1 || endIdx == -1) return -1;
    
    dist[startIdx] = 0; // расстояние до себя же 0
    
    for (size_t i = 0; i < nodes.size(); i++) {
        // находим неотvisited узел с минимальным расстоянием
        int u = -1;
        int minDist = INT_MAX;
        for (size_t j = 0; j < nodes.size(); j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;
        
        // обновляем расстояния до соседей
        for (size_t v = 0; v < nodes.size(); v++) {
            if (u != v) {
                int weight = graph.getWeight(nodes[u], nodes[v]);
                if (weight != -1 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    
    return dist[endIdx] == INT_MAX ? -1 : dist[endIdx];
}

void task6() {
    setlocale(0, "");
    
    std::cout << "=== Задание 6: Оптимизация маршрутов ===\n\n";
    
    GraphHash graph(100);
    std::vector<std::string> nodes;
    
    // Ввод количества рёбер
    int m;
    std::cout << "Введите количество маршрутов: ";
    std::cin >> m;
    
    std::cout << "Введите маршруты в формате: ОТКУДА КУДА ЗАДЕРЖКА\n";
    
    // Читаем рёбра
    for (int i = 0; i < m; i++) {
        std::string from, to;
        int weight;
        std::cin >> from >> to >> weight;
        
        graph.addEdge(from, to, weight);
        
        // Добавляем вершины в список (если их там ещё нет)
        bool found = false;
        for (const auto& node : nodes) {
            if (node == from) { found = true; break; }
        }
        if (!found) nodes.push_back(from);
        
        found = false;
        for (const auto& node : nodes) {
            if (node == to) { found = true; break; }
        }
        if (!found) nodes.push_back(to);
    }
    
    // Ввод начального и конечного серверов
    std::string start, end;
    std::cout << "\nВведите начальный сервер: ";
    std::cin >> start;
    std::cout << "Введите конечный сервер: ";
    std::cin >> end;
    
    // Запускаем алгоритм Дейкстры
    int minDelay = dijkstra(graph, start, end, nodes);
    
    std::cout << "Минимальная задержка от " << start << " до " << end << ": ";
    if (minDelay == -1) {
        std::cout << "маршрут не найден\n";
    } else {
        std::cout << minDelay << "\n";
    }
}