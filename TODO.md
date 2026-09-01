# Core Architecture Guidelines (Library-Wide Policies)

- **DO NOT USE THE C++ STANDARD LIBRARY VERSION OF ANY OF THE GIVEN DATA
STRUCTURES OR ALGORITHMS**

- **C++ Standard Iterators:** We need to implement Forward, Bidirectional, or
Random Access iterators where applicable (e.g. Tree Traversals are implemented
as iterators). Meaning, we need to implement `operator++`, `operator--`,
`operator*`, etc. to be able to use stuff like:
```c++
for (int value : our_linked_list) {
```

- **Template Constraints:** We need to constrain template parameters (e.g.,
requiring `std::totally_ordered` for sorting algorithms). As in, we need to add
```c++
requires std::totally_ordered<T>
```
to make sure something like
```c++
template <typename T> void QuickSort(T* array)
```
can't accept anything that doesn't have `operator<` or `operator>`
implemented.

---

# 1. Linear Data Structures

- [ ] Dynamic Array
- [ ] Linked Lists
    - [ ] Singly Linked
        - [ ] Regular
        - [ ] Circular
    - [ ] Doubly Linked
        - [ ] Regular
        - [ ] Circular
    - [ ] Intrusive Linked List
- [ ] Stack
    - [ ] Array-based
    - [ ] Linked List-based
- [ ] Queue
    - [ ] Array-based
    - [ ] Linked List-based
- [ ] Circular Buffer (Ring Buffer)
- [ ] Lock-Free Ring Buffer (Single-Producer, Single-Consumer using
`std::atomic`)
- [ ] Double-Ended Queue (Deque)
- [ ] Sparse Set (ECS / SoA Memory Layout)

# 2. Sorting Algorithms

- [ ] Bubble Sort
- [ ] Selection Sort
- [ ] Insertion Sort
- [ ] Counting Sort
- [ ] Shellsort
- [ ] Radix Sort
- [ ] Mergesort
- [ ] Quicksort
- [ ] Heapsort
- [ ] Hybrid / Production Sorts
    - [ ] Introsort (Quicksort + Heapsort + Insertion Sort)
    - [ ] TimSort (Optimized Merge Sort + Insertion Sort)

# 3. Hashing & Caches

- [ ] Hash Table (Separate Chaining)
- [ ] Hash Table (Open Addressing: Linear Probing)
- [ ] Hash Table (Open Addressing: Quadratic Probing)
- [ ] Hash Table (Open Addressing: Double Hashing)
- [ ] Bloom Filter (Probabilistic)
- [ ] LRU Cache (Least Recently Used)
- [ ] LFU Cache (Least Frequently Used)
- [ ] Cuckoo Hashing

# 4. Basic Trees & Priority Queues

- [ ] Binary Tree
- [ ] Binary Search Tree (BST)
- [ ] Binary Heap (Min/Max)
- [ ] *d*-Heaps
- [ ] Leftist Heaps
- [ ] Skew Heaps
- [ ] Binomial Queues
- [ ] Pairing Heaps
- [ ] Fibonacci Heaps
- [ ] Merkle Tree (Cryptographic Hash Tree)

# 5. Self-Balancing, Database & Advanced Trees

- [ ] Skip List (Probabilistic Layered Linking)
- [ ] Treaps (BST + Heap property)
- [ ] AVL Trees
    - [ ] Single Rotation
    - [ ] Double Rotation
- [ ] Splay Trees
    - [ ] Bottom-Up
    - [ ] Top-Down
- [ ] Red-Black Trees
    - [ ] Bottom-Up Insertion
    - [ ] Top-Down Insertion
    - [ ] Top-Down Deletion
- [ ] B-Trees
- [ ] B+ Trees
- [ ] LSM-Tree (Log-Structured Merge-Tree)

# 6. String Algorithms & Data Structures

- [ ] Trie (Prefix Tree)
- [ ] Radix Tree / Patricia Trie (Compressed Prefix Tree)
- [ ] String Search: Rabin-Karp (Rolling hash)
- [ ] String Search: Knuth-Morris-Pratt (KMP)
- [ ] String Search: Boyer-Moore
- [ ] Suffix Arrays
- [ ] Aho-Corasick Automaton
- [ ] Suffix Trees

# 7. Spatial & Range Data Structures (Engine Ops)

- [ ] Sparse Table (Immutable Range Minimum Query)
- [ ] Fenwick Tree (Binary Indexed Tree)
- [ ] Quadtree
- [ ] Octree
- [ ] Segment Tree
- [ ] Bounding Volume Hierarchy (BVH - Object grouping)
- [ ] *k*-*d* Trees
- [ ] R-Tree

# 8. Disjoint Sets

- [ ] The Disjoint Sets Class (Union-Find)
    - [ ] Path Compression
    - [ ] Union by Rank

# 9. Graph Algorithms

- [ ] Breadth-First Search (BFS) & Depth-First Search (DFS)
- [ ] Topological Sort
- [ ] Unweighted Shortest Paths
- [ ] Dijkstra's Algorithm
- [ ] Prim's Algorithm (Minimum Spanning Tree)
- [ ] Kruskal's Algorithm (Minimum Spanning Tree)
- [ ] A\* Search Algorithm
- [ ] Bellman-Ford Algorithm (Graphs with Negative Edge Costs)
- [ ] Acyclic Graphs Shortest Path
- [ ] Floyd-Warshall Algorithm (All-Pairs Shortest Path)
- [ ] Bridges and Articulation Points
- [ ] Tarjan's Algorithm (Strongly Connected Components)
- [ ] Kosaraju's Algorithm (Strongly Connected Components)
- [ ] Hopcroft-Karp (Maximum Bipartite Matching)

# 10. Data Compression & Encoding

- [ ] Run-Length Encoding (RLE)
- [ ] Huffman Coding (Huffman Trees)
