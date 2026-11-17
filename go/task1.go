package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func precedence(op rune) int {
	if op == '+' || op == '-' {
		return 1
	}
	if op == '*' || op == '/' {
		return 2
	}
	return 0
}

func infixToPostfix(s string) string {
	stack := &Stack[rune]{}
	var result strings.Builder

	currentNumber := ""
	inNumber := false

	for _, ch := range s {
		if ch == ' ' {
			if inNumber {
				result.WriteString(currentNumber + " ")
				currentNumber = ""
				inNumber = false
			}
			continue
		}

		if unicode.IsDigit(ch) {
			currentNumber += string(ch)
			inNumber = true
		} else {
			if inNumber {
				result.WriteString(currentNumber + " ")
				currentNumber = ""
				inNumber = false
			}

			if ch == '(' {
				stack.SPush(ch)
			} else if ch == ')' {
				for !stack.SEmpty() && stack.STop() != '(' {
					result.WriteRune(stack.STop())
					result.WriteRune(' ')
					stack.SPop()
				}
				if !stack.SEmpty() {
					stack.SPop()
				}
			} else {
				for !stack.SEmpty() && precedence(stack.STop()) >= precedence(ch) {
					result.WriteRune(stack.STop())
					result.WriteRune(' ')
					stack.SPop()
				}
				stack.SPush(ch)
			}
		}
	}

	if inNumber {
		result.WriteString(currentNumber + " ")
	}

	for !stack.SEmpty() {
		result.WriteRune(stack.STop())
		result.WriteRune(' ')
		stack.SPop()
	}

	return strings.TrimSpace(result.String())
}

func task1() {
	fmt.Println("=== Задание 1: Преобразование инфиксной нотации в постфиксную ===")
	fmt.Println()
	fmt.Print("Введите арифметическое выражение (например, 123+45*2): ")

	reader := bufio.NewReader(os.Stdin)
	expr, _ := reader.ReadString('\n')
	expr = strings.TrimSpace(expr)

	if expr == "" {
		fmt.Println("Ошибка: выражение пустое!")
		return
	}

	postfix := infixToPostfix(expr)
	fmt.Println("Инфиксная:  ", expr)
	fmt.Println("Постфиксная:", postfix)
}