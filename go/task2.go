package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func task2(args []string) {
	filename := "data.txt"
	for i := 0; i < len(args); i++ {
		if args[i] == "--file" && i+1 < len(args) {
			filename = args[i+1]
			break
		}
	}

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка: не удалось открыть файл", filename)
		return
	}
	defer file.Close()

	mySet := NewStringHashSet(100)

	fmt.Println("--- Начало обработки файла", filename, "---")

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		if len(parts) != 2 {
			continue
		}

		command := parts[0]
		value := parts[1]

		switch command {
		case "SETADD":
			mySet.Add(value)
			fmt.Println("Добавлено:", value)
		case "SETDEL":
			mySet.Remove(value)
			fmt.Println("Удалено:", value)
		case "SET_AT":
			exists := mySet.Contains(value)
			if exists {
				fmt.Printf("Проверка %s: есть\n", value)
			} else {
				fmt.Printf("Проверка %s: нет\n", value)
			}
		}
	}
	fmt.Println("--- Обработка завершена ---")
}