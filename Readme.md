# Project: Tree with Iterators

## Introduction
This project implements a generic tree structure with `k`-ary trees, meaning that each node in the tree can have up to `k` children. The tree is templated to allow storing any type of data (e.g., integers, complex numbers, etc.). Additionally, the project includes various traversal iterators such as pre-order, post-order, in-order, and breadth-first search (BFS).

## Class Hierarchy

### 1. **Node Class**
- **Location:** `node.hpp`
- **Description:**
  The `Node<T>` class represents a single node in the tree. Each node stores:
  - A value of type `T` (which can be any type, such as `int`, `double`, or `Complex`).
  - A list (or vector) of child nodes, where the maximum number of children is determined by the template parameter `K`.

- **Key Members:**
  - `T value`: The value stored in the node.
  - `std::vector<std::shared_ptr<Node<T>>> children`: A vector of child nodes using `shared_ptr` for efficient memory management.

### 2. **Tree Class**
- **Location:** `tree.hpp`
- **Description:**
  The `Tree<T, K>` class represents the entire tree structure. It holds the root node and manages the operations on the tree, such as adding nodes and traversing the tree. The tree supports up to `K` children for each node, where `K` is a template parameter.

- **Key Members:**
  - `std::shared_ptr<Node<T>> root`: The root node of the tree.
  - `size_t k`: The maximum number of children allowed per node.

- **Key Methods:**
  - `add_root(Node<T>& node)`: Adds the root node to the tree.
  - `add_child(Node<T>& parent, Node<T>& child)`: Adds a child node to the specified parent node.
  - `delete_tree(std::shared_ptr<Node<T>> node)`: Recursively deletes the tree from the given node (handled by `shared_ptr`).

### 3. **Iterator Classes**
- **Location:** `iterators.hpp`
- **Description:**
  Several iterator classes are provided to traverse the tree in different ways. Each iterator implements standard C++ iterator protocols, allowing usage in range-based for loops.

- **Iterators:**
  - `PreOrderIterator`: Traverses the tree in pre-order (root, then children).
  - `PostOrderIterator`: Traverses the tree in post-order (children, then root).
  - `InOrderIterator`: Traverses the tree in in-order (for binary trees, it's left, root, right).
  - `BFSIterator`: Traverses the tree level by level (breadth-first search).

### 4. **Complex Class**
- **Location:** `Complex.hpp`
- **Description:**
  This class is used as a demonstration of templating with custom data types. It represents a complex number with real and imaginary parts.

- **Key Members:**
  - `double real`: The real part of the complex number.
  - `double imag`: The imaginary part of the complex number.

- **Key Methods:**
  - `Complex operator+(const Complex& other)`: Adds two complex numbers.
  - `Complex operator*(const Complex& other)`: Multiplies two complex numbers.

## External Libraries

### 1. **Standard Template Library (STL)**
  - **Headers:** `<memory>`, `<vector>`, `<queue>`, `<stack>`, `<iostream>`, etc.
  - **Usage:**
    - `std::shared_ptr`: Used for memory management of the nodes to automatically handle object destruction.
    - `std::vector`: Used for storing the children of each node.
    - `std::queue` and `std::stack`: Used in the BFS and DFS implementations for traversing the tree.

### 2. **SFML (Optional)**
  - **Headers:** `<SFML/Graphics.hpp>`, `<SFML/Window.hpp>`
  - **Usage:** If you're using SFML, this library can be used for graphical visualization of the tree structure, though it is optional. The tree logic itself does not depend on SFML, but it can be extended for visualization purposes.

## Compilation Instructions

To compile the project, use the following command in the terminal:
```bash
g++ -std=c++17 -Wall -I/usr/include/SFML -c -o main.o main.cpp
g++ -std=c++17 -Wall -o TreeApp main.o Complex.o -lsfml-graphics -lsfml-window -lsfml-system
./test - in order to run test file.
./main - in order to run the main file
```
