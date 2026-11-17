package main

import (
	"fmt"
	"sort"
)

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func insertTree(root **TreeNode, val int) {
	if *root == nil {
		*root = &TreeNode{Val: val}
		return
	}
	if val < (*root).Val {
		insertTree(&(*root).Left, val)
	} else if val > (*root).Val {
		insertTree(&(*root).Right, val)
	}
}

func collectForks(node *TreeNode, forks *[]int) {
	if node == nil {
		return
	}
	if node.Left != nil && node.Right != nil {
		*forks = append(*forks, node.Val)
	}
	collectForks(node.Left, forks)
	collectForks(node.Right, forks)
}

func task5() {
	fmt.Println("=== Задание 5: Вывод развилок ===")
	fmt.Println()
	fmt.Print("Введите числа (0 для завершения): ")

	var root *TreeNode
	var val int

	for {
		fmt.Scan(&val)
		if val == 0 {
			break
		}
		insertTree(&root, val)
	}

	var forks []int
	collectForks(root, &forks)
	sort.Ints(forks)

	fmt.Print("Развилки: ")
	for _, x := range forks {
		fmt.Print(x, " ")
	}
	fmt.Println()
}