package main

import (
	"fmt"
	"math"
)

func containsStr(slice []string, val string) bool {
	for _, v := range slice {
		if v == val {
			return true
		}
	}
	return false
}

func dijkstra(graph *GraphHash, start, end string, nodes []string) int {
	dist := make([]int, len(nodes))
	visited := make([]bool, len(nodes))
	for i := range dist {
		dist[i] = math.MaxInt32
	}

	startIdx, endIdx := -1, -1
	for i, node := range nodes {
		if node == start {
			startIdx = i
		}
		if node == end {
			endIdx = i
		}
	}

	if startIdx == -1 || endIdx == -1 {
		return -1
	}

	dist[startIdx] = 0

	for i := 0; i < len(nodes); i++ {
		u := -1
		minDist := math.MaxInt32
		for j := 0; j < len(nodes); j++ {
			if !visited[j] && dist[j] < minDist {
				minDist = dist[j]
				u = j
			}
		}

		if u == -1 {
			break
		}
		visited[u] = true

		for v := 0; v < len(nodes); v++ {
			if u != v {
				weight := graph.GetWeight(nodes[u], nodes[v])
				if weight != -1 && dist[u] != math.MaxInt32 && dist[u]+weight < dist[v] {
					dist[v] = dist[u] + weight
				}
			}
		}
	}

	if dist[endIdx] == math.MaxInt32 {
		return -1
	}
	return dist[endIdx]
}

func task6() {
	fmt.Println("=== Задание 6: Оптимизация маршрутов ===")
	fmt.Println()

	var m int
	fmt.Print("Введите количество маршрутов: ")
	fmt.Scan(&m)

	if m <= 0 {
		fmt.Println("Ошибка: количество маршрутов должно быть > 0")
		return
	}

	graph := NewGraphHash(100)
	var nodes []string

	fmt.Println("Введите маршруты в формате: ОТКУДА КУДА ЗАДЕРЖКА")
	for i := 0; i < m; i++ {
		var from, to string
		var weight int
		fmt.Printf("Маршрут %d: ", i+1)
		fmt.Scan(&from, &to, &weight)

		graph.AddEdge(from, to, weight)

		if !containsStr(nodes, from) {
			nodes = append(nodes, from)
		}
		if !containsStr(nodes, to) {
			nodes = append(nodes, to)
		}
	}

	var start, end string
	fmt.Print("\nВведите начальный сервер: ")
	fmt.Scan(&start)
	fmt.Print("Введите конечный сервер: ")
	fmt.Scan(&end)

	minDelay := dijkstra(graph, start, end, nodes)

	fmt.Printf("Минимальная задержка от %s до %s: ", start, end)
	if minDelay == -1 {
		fmt.Println("маршрут не найден")
	} else {
		fmt.Println(minDelay)
	}
}