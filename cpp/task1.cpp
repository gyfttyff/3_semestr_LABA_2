#include "task1.h"
#include "structures.h"
#include <iostream>
#include <string>
#include <cctype>

// функция приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infixToPostfix(const std::string& str) {
    Stack<char> st;
    std::string result = "";

    // буфер многозначного числа
    std::string current_number = "";  
    bool in_number = false;           

    for (char c : str) {
        if (c == ' ') {
            if (in_number) {
                result += current_number + " ";
                current_number = "";
                in_number = false;
            }
            continue; // игнорируем пробелы
        }
        
        if (isdigit(c)) { // если цифра
            current_number += c;         
            in_number = true;             
        }
        else {
            // если встретили НЕ цифру сбрасываем накопленное число в результат
            if (in_number) {
                result += current_number + " ";
                current_number = "";
                in_number = false;
            }

            if (c == '(') {
                st.SPush(c);
            } 
            else if (c == ')') {
                while (!st.SEmpty() && st.STop() != '(') {
                    result += st.STop();
                    result += ' ';
                    st.SPop();
                }
                if (!st.SEmpty()) st.SPop(); // Удаляем саму '('
            } 
            else { // это оператор +, -, *, /
                while (!st.SEmpty() && precedence(st.STop()) >= precedence(c)) {
                    result += st.STop();
                    result += ' ';
                    st.SPop();
                }
                st.SPush(c);
            }
        }
    }
    
    // если выражение закончилось числом, сбрасываем остаток буфера в результат
    if (in_number) {
        result += current_number + " ";
    }

    // выкидываем всё, что осталось в стеке
    while (!st.SEmpty()) {
        result += st.STop();
        result += ' ';
        st.SPop();
    }
    return result;
}

void task1() {
    setlocale(0, "");
    
    std::cout << "Введите арифметическое выражение (например, 123+45*2): ";
    std::string expr;
    std::getline(std::cin, expr); // getline читает всю строку до нажатия Enter
    
    if (expr.empty()) {
        std::cout << "Ошибка: выражение пустое!\n";
        return;
    }

    std::cout << "Инфиксная:   " << expr << "\n";
    std::cout << "Постфиксная: " << infixToPostfix(expr) << "\n";
}