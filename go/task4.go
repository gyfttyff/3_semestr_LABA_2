package main

import "fmt"

func task4() {
	var n int
	fmt.Print("Введите количество элементов: ")
	fmt.Scan(&n)

	arr := &Array[string]{}
	arr.Init()

	fmt.Print("Введите элементы через пробел: ")
	for i := 0; i < n; i++ {
		var val string
		fmt.Scan(&val)
		arr.MPush(val)
	}

	total := 1 << n

	fmt.Println("Результат:")
	for i := 0; i < total; i++ {
		fmt.Print("{")
		first := true
		for j := 0; j < n; j++ {
			if (i>>j)&1 == 1 {
				if !first {
					fmt.Print(", ")
				}
				fmt.Print(arr.Data[j])
				first = false
			}
		}
		fmt.Print("} ")
	}
	fmt.Println()
}