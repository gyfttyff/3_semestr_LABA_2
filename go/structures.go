package main

import "fmt"

type Node[T any] struct {
	Value T
	Next  *Node[T]
}

type Stack[T any] struct {
	Head *Node[T]
}

func (s *Stack[T]) SEmpty() bool {
	return s.Head == nil
}

func (s *Stack[T]) SPush(v T) {
	s.Head = &Node[T]{Value: v, Next: s.Head}
}

func (s *Stack[T]) STop() T {
	if s.SEmpty() {
		var zero T
		return zero
	}
	return s.Head.Value
}

func (s *Stack[T]) SPop() {
	if s.SEmpty() {
		return
	}
	s.Head = s.Head.Next
}

type Array[T any] struct {
	Data     []T
	Size     int
	Capacity int
}

func (a *Array[T]) Init() {
	a.Capacity = 1
	a.Size = 0
	a.Data = make([]T, a.Capacity)
}

func (a *Array[T]) MPush(v T) {
	if a.Size == a.Capacity {
		newData := make([]T, a.Capacity*2)
		copy(newData, a.Data)
		a.Data = newData
		a.Capacity *= 2
	}
	a.Data[a.Size] = v
	a.Size++
}

func (a *Array[T]) MDelInd(idx int) {
	if idx < 0 || idx >= a.Size {
		return
	}
	copy(a.Data[idx:], a.Data[idx+1:a.Size])
	a.Size--
}

type ForwardList[T any] struct {
	Head *Node[T]
}

func (l *ForwardList[T]) FPushFront(v T) {
	l.Head = &Node[T]{Value: v, Next: l.Head}
}

func (l *ForwardList[T]) FPushBack(v T) {
	n := &Node[T]{Value: v, Next: nil}
	if l.Head == nil {
		l.Head = n
		return
	}
	cur := l.Head
	for cur.Next != nil {
		cur = cur.Next
	}
	cur.Next = n
}

func (l *ForwardList[T]) FDelValue(v T) {
	var prev *Node[T]
	cur := l.Head
	for cur != nil {
		if fmt.Sprintf("%v", cur.Value) == fmt.Sprintf("%v", v) {
			if prev == nil {
				l.Head = cur.Next
			} else {
				prev.Next = cur.Next
			}
			return
		}
		prev = cur
		cur = cur.Next
	}
}