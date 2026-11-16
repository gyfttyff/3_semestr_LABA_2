#include "task3.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <numeric>

// рекурсивная функция backtracking
// nums массив чисел
// subsets массив подмножеств 
// sums массив текущих сумм каждого подмножества
// target целевая сумма
// index индекс текущего числа в nums
bool solve(const std::vector<int>& nums, 
           std::vector<std::vector<int>>& subsets, 
           std::vector<int>& sums, 
           int target, 
           int index) {
    
    // елси все числа распределены
    if (index == nums.size()) {
        // проверяем все подмножества набрали целевую сумму
        for (int s : sums) {
            if (s != target) return false;
        }
        return true;
    }

    // пытаемся положить текущее число в каждое подмножество
    for (int i = 0; i < subsets.size(); i++) {
        // если добавление не превысит целевую сумму
        if (sums[i] + nums[index] <= target) {
            // кладем число в подмножество
            subsets[i].push_back(nums[index]);
            sums[i] += nums[index];
            
            // Рекурсивно пытаемся распределить остальные числа
            if (solve(nums, subsets, sums, target, index + 1)) {
                return true; // решение!
            }
            
            // backtracking если не получилось, забираем число обратно
            subsets[i].pop_back();
            sums[i] -= nums[index];
        }
    }
    
    return false; // не удалось найти решение
}

// для вывода разбиения
void printPartition(const std::vector<std::vector<int>>& subsets, int target) {
    std::cout << "Целевая сумма: " << target << "\n";
    for (size_t i = 0; i < subsets.size(); i++) {
        std::cout << "  Подмножество " << (i + 1) << ": {";
        int sum = 0;
        for (size_t j = 0; j < subsets[i].size(); j++) {
            std::cout << subsets[i][j];
            sum += subsets[i][j];
            if (j < subsets[i].size() - 1) std::cout << ", ";
        }
        std::cout << "} (сумма = " << sum << ")\n";
    }
    std::cout << "\n";
}

void task3() {
    setlocale(0, "");
    
    std::cout << "=== Задание 3: Разбиение множества ===\n\n";
    
    HashSet mySet(100);
    
    std::cout << "Введите числа множества (0 для завершения):\n";
    int num;
    std::vector<int> nums;
    
    while (std::cin >> num && num != 0) {
    if (!mySet.contains(num)) {  // нет ли уже в множестве
        mySet.add(num);          // добавляем в HashSet
        nums.push_back(num);     // и сразу в вектор
    }
}
    
    if (nums.empty()) {
        std::cout << "Ошибка: множество пустое!\n";
        return;
    }
    
    // считаем общую сумму
    int totalSum = 0;
    for (int n : nums) {
        totalSum += n;
    }
    
    std::cout << "\nМножество: {";
    for (size_t i = 0; i < nums.size(); i++) {
        std::cout << nums[i];
        if (i < nums.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";
    std::cout << "Общая сумма: " << totalSum << "\n\n";
    
    // все возможные целевые суммы (делители общей суммы)
    std::cout << "Возможные разбиения:\n\n";
    bool foundAny = false;
    
    for (int target = 1; target <= totalSum / 2; target++) {
        if (totalSum % target != 0) continue; // целевая сумма должна быть делителем
        
        int numSubsets = totalSum / target; // Количество подмножеств
        
        std::vector<std::vector<int>> subsets(numSubsets);
        std::vector<int> sums(numSubsets, 0);
        
        if (solve(nums, subsets, sums, target, 0)) {
            printPartition(subsets, target);
            foundAny = true;
        }
    }
    
    if (!foundAny) {
        std::cout << "Множество невозможно разбить на подмножества с равными суммами.\n";
    }
}