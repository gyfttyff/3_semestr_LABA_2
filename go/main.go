package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("\n========== ЛАБОРАТОРНАЯ РАБОТА №2 ==========")
		fmt.Println("1. Стек (инфиксная -> постфиксная)")
		fmt.Println("2. АТД Множество (из файла)")
		fmt.Println("3. Разбиение множества")
		fmt.Println("4. Различные подмассивы")
		fmt.Println("5. Развилки бинарного дерева")
		fmt.Println("6. Оптимизация маршрутов (хеш-таблица)")
		fmt.Println("7. LRU кэш")
		fmt.Println("0. Выход")
		fmt.Println("============================================")
		fmt.Print("Выберите задачу: ")

		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)

		switch line {
		case "1":
			task1()
		case "2":
			task2(os.Args[1:])
		case "3":
			task3()
		case "4":
			task4()
		case "5":
			task5()
		case "6":
			task6()
		case "7":
			task7()
		case "0":
			fmt.Println("Выход из программы. Удачи!")
			return
		default:
			fmt.Println("Нет такой задачи!")
		}

		fmt.Print("\nНажмите Enter для продолжения...")
		reader.ReadString('\n')
	}
}