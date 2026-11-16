#include "task5.h"
#include <iostream>
#include <vector>
#include <algorithm>


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// вставка
void insert(TreeNode*& root, int val) {
    if (!root) {
        root = new TreeNode(val);
        return;
    }
    if (val < root->val) {
        insert(root->left, val);
    } else if (val > root->val) {
        insert(root->right, val);
    }
    // если val == root->val, не делаем ничего дубликаты не добавляем
}

// Рекурсивный сбор развилок
void collectForks(TreeNode* node, std::vector<int>& forks) {
    if (!node) return;
    
    // если у узла есть оба ребёнка 
    if (node->left != nullptr && node->right != nullptr) {
        forks.push_back(node->val);
    }
    
    collectForks(node->left, forks);
    collectForks(node->right, forks);
}


void clearTree(TreeNode* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void task5() {
    setlocale(0, "");
    
    std::cout << "=== Задание 5: Вывод развилок ===\n\n";
    std::cout << "Введите числа (0 для завершения): ";
    
    TreeNode* root = nullptr;
    int val;
    
    while (std::cin >> val && val != 0) {
        insert(root, val);
    }
    
    std::vector<int> forks;
    collectForks(root, forks);
    
    // сортируем по возрастанию
    std::sort(forks.begin(), forks.end());
    
    std::cout << "Развилки: ";
    for (int x : forks) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    
    clearTree(root);
}