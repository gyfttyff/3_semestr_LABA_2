package main

import "fmt"

func solve(nums []int, subsets [][]int, sums []int, target int, index int) bool {
	if index == len(nums) {
		for _, s := range sums {
			if s != target {
				return false
			}
		}
		return true
	}

	for i := 0; i < len(subsets); i++ {
		if sums[i]+nums[index] <= target {
			subsets[i] = append(subsets[i], nums[index])
			sums[i] += nums[index]

			if solve(nums, subsets, sums, target, index+1) {
				return true
			}

			subsets[i] = subsets[i][:len(subsets[i])-1]
			sums[i] -= nums[index]
		}
	}
	return false
}

func printPartition(subsets [][]int, target int) {
	fmt.Printf("Целевая сумма: %d\n", target)
	for i, subset := range subsets {
		fmt.Printf("  Подмножество %d: {", i+1)
		sum := 0
		for j, val := range subset {
			fmt.Print(val)
			sum += val
			if j < len(subset)-1 {
				fmt.Print(", ")
			}
		}
		fmt.Printf("} (сумма = %d)\n", sum)
	}
	fmt.Println()
}

func task3() {
	fmt.Println("=== Задание 3: Разбиение множества ===")
	fmt.Println()

	mySet := NewHashSet(100)
	var nums []int

	fmt.Println("Введите числа множества (0 для завершения):")
	var num int
	for {
		fmt.Scan(&num)
		if num == 0 {
			break
		}
		if !mySet.Contains(num) {
			mySet.Add(num)
			nums = append(nums, num)
		}
	}

	if len(nums) == 0 {
		fmt.Println("Ошибка: множество пустое!")
		return
	}

	totalSum := 0
	for _, n := range nums {
		totalSum += n
	}

	fmt.Printf("\nМножество: {")
	for i, n := range nums {
		fmt.Print(n)
		if i < len(nums)-1 {
			fmt.Print(", ")
		}
	}
	fmt.Printf("}\n")
	fmt.Printf("Общая сумма: %d\n\n", totalSum)

	fmt.Println("Возможные разбиения:\n")
	foundAny := false

	for target := 1; target <= totalSum/2; target++ {
		if totalSum%target != 0 {
			continue
		}

		numSubsets := totalSum / target
		subsets := make([][]int, numSubsets)
		sums := make([]int, numSubsets)

		if solve(nums, subsets, sums, target, 0) {
			printPartition(subsets, target)
			foundAny = true
		}
	}

	if !foundAny {
		fmt.Println("Множество невозможно разбить на подмножества с равными суммами.")
	}
}