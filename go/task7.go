package main

import "fmt"

type CacheItem struct {
	Key      int
	Value    int
	LastUsed int
	IsValid  bool
}

func findInCache(cache []CacheItem, capacity int, key int, timeCounter *int) int {
	for i := 0; i < capacity; i++ {
		if cache[i].IsValid && cache[i].Key == key {
			*timeCounter++
			cache[i].LastUsed = *timeCounter
			return i
		}
	}
	return -1
}

func cacheSet(cache []CacheItem, capacity int, key int, value int, timeCounter *int) {
	idx := findInCache(cache, capacity, key, timeCounter)
	if idx != -1 {
		cache[idx].Value = value
		return
	}

	oldestIdx := -1
	minTime := 1<<31 - 1

	for i := 0; i < capacity; i++ {
		if !cache[i].IsValid {
			oldestIdx = i
			break
		}
		if cache[i].LastUsed < minTime {
			minTime = cache[i].LastUsed
			oldestIdx = i
		}
	}

	*timeCounter++
	cache[oldestIdx] = CacheItem{Key: key, Value: value, LastUsed: *timeCounter, IsValid: true}
}

func cacheGet(cache []CacheItem, capacity int, key int, timeCounter *int) int {
	idx := findInCache(cache, capacity, key, timeCounter)
	if idx != -1 {
		return cache[idx].Value
	}
	return -1
}

func task7() {
	fmt.Println("=== Задание 7: LRU Кэш ===")
	fmt.Println()

	var cap int
	fmt.Print("Введите ёмкость кэша: ")
	fmt.Scan(&cap)

	if cap <= 0 {
		fmt.Println("Ошибка: ёмкость должна быть > 0")
		return
	}

	var q int
	fmt.Print("Введите количество запросов: ")
	fmt.Scan(&q)

	cache := make([]CacheItem, cap)
	timeCounter := 0

	fmt.Println("\nРезультаты запросов:")
	for i := 0; i < q; i++ {
		var command string
		fmt.Scan(&command)

		if command == "SET" {
			var key, value int
			fmt.Scan(&key, &value)
			cacheSet(cache, cap, key, value, &timeCounter)
			fmt.Printf("SET %d %d → OK\n", key, value)
		} else if command == "GET" {
			var key int
			fmt.Scan(&key)
			result := cacheGet(cache, cap, key, &timeCounter)
			fmt.Printf("GET %d → %d\n", key, result)
		} else {
			fmt.Printf("Неизвестная команда: %s\n", command)
		}
	}
}