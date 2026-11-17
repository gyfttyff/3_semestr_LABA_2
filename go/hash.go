package main

type HashSet struct {
	table    []int
	state    []int
	capacity int
}

func NewHashSet(capacity int) *HashSet {
	return &HashSet{
		table:    make([]int, capacity),
		state:    make([]int, capacity),
		capacity: capacity,
	}
}

func (h *HashSet) hash(key int) int {
	return (key%h.capacity + h.capacity) % h.capacity
}

func (h *HashSet) Add(key int) {
	idx := h.hash(key)
	for h.state[idx] == 1 {
		if h.table[idx] == key {
			return
		}
		idx = (idx + 1) % h.capacity
	}
	h.table[idx] = key
	h.state[idx] = 1
}

func (h *HashSet) Contains(key int) bool {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			return true
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
	return false
}

func (h *HashSet) Remove(key int) {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			h.state[idx] = 2
			return
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
}

type StringHashSet struct {
	table    []string
	state    []int
	capacity int
}

func NewStringHashSet(capacity int) *StringHashSet {
	return &StringHashSet{
		table:    make([]string, capacity),
		state:    make([]int, capacity),
		capacity: capacity,
	}
}

func (h *StringHashSet) hash(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*31 + int(c)) % h.capacity
	}
	return (hash + h.capacity) % h.capacity
}

func (h *StringHashSet) Add(key string) {
	idx := h.hash(key)
	for h.state[idx] == 1 {
		if h.table[idx] == key {
			return
		}
		idx = (idx + 1) % h.capacity
	}
	h.table[idx] = key
	h.state[idx] = 1
}

func (h *StringHashSet) Contains(key string) bool {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			return true
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
	return false
}

func (h *StringHashSet) Remove(key string) {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			h.state[idx] = 2
			return
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
}

type DoubleHash struct {
	table    []string
	state    []int
	capacity int
}

func NewDoubleHash(capacity int) *DoubleHash {
	return &DoubleHash{
		table:    make([]string, capacity),
		state:    make([]int, capacity),
		capacity: capacity,
	}
}

func (h *DoubleHash) hash1(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*31 + int(c)) % h.capacity
	}
	return hash
}

func (h *DoubleHash) hash2(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*37 + int(c)) % (h.capacity - 1)
	}
	return hash + 1
}

func (h *DoubleHash) Insert(key string) {
	idx := h.hash1(key)
	step := h.hash2(key)
	for h.state[idx] == 1 {
		if h.table[idx] == key {
			return
		}
		idx = (idx + step) % h.capacity
	}
	h.table[idx] = key
	h.state[idx] = 1
}

func (h *DoubleHash) Contains(key string) bool {
	idx := h.hash1(key)
	step := h.hash2(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			return true
		}
		idx = (idx + step) % h.capacity
		if idx == startIdx {
			break
		}
	}
	return false
}

type Edge struct {
	From     string
	To       string
	Weight   int
	Occupied bool
}

type GraphHash struct {
	table    []Edge
	capacity int
}

func NewGraphHash(capacity int) *GraphHash {
	return &GraphHash{
		table:    make([]Edge, capacity),
		capacity: capacity,
	}
}

func (h *GraphHash) hash(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*31 + int(c)) % h.capacity
	}
	return hash
}

func (h *GraphHash) AddEdge(from, to string, weight int) {
	key := from + "->" + to
	idx := h.hash(key)
	for h.table[idx].Occupied {
		if h.table[idx].From == from && h.table[idx].To == to {
			h.table[idx].Weight = weight
			return
		}
		idx = (idx + 1) % h.capacity
	}
	h.table[idx] = Edge{From: from, To: to, Weight: weight, Occupied: true}
}

func (h *GraphHash) GetWeight(from, to string) int {
	key := from + "->" + to
	idx := h.hash(key)
	start := idx
	for h.table[idx].Occupied {
		if h.table[idx].From == from && h.table[idx].To == to {
			return h.table[idx].Weight
		}
		idx = (idx + 1) % h.capacity
		if idx == start {
			break
		}
	}
	return -1
}