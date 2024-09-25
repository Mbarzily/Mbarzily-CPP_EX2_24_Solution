// matanayabarzilay@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <SFML/Graphics.hpp>
#include <stack>
#include <queue>
#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <type_traits>


// Forward declaration of iterators
template<typename T, size_t K>
class PreOrderIterator;

template<typename T, size_t K>
class PostOrderIterator;

template<typename T, size_t K>
class InOrderIterator;

template<typename T>
class BFSIterator;

template<typename T, size_t K>
class DFSIterator;

template<typename T>
class HeapIterator;

template<typename T, size_t K = 2>
class Tree {
public:
    std::shared_ptr<Node<T>> root;
    size_t k;
  

    Tree(size_t k = K) : root(nullptr), k(k) {}
        ~Tree() {
        delete_tree(root);
    }
    void print() const;
    void drawTree(sf::RenderWindow& window, const sf::Font& font) const;

    void drawNode(sf::RenderWindow& window, const sf::Font& font, const std::shared_ptr<Node<T>>& node, float x, float y) const;
    void drawEdge(sf::RenderWindow& window, float x1, float y1, float x2, float y2) const;
    int getTreeDepth(const std::shared_ptr<Node<T>>& node) const;
    void treeToHeap() {HeapIterator<T> heapIt(root);}
    void add_root(Node<T> node) {root = std::make_shared<Node<T>>(std::move(node));}

    void add_sub_node(Node<T>& parent, Node<T> child) {
    auto parent_ptr = find_node(root, parent.value);
    if (parent_ptr) {
        if (parent_ptr->children.size() < k) {
            parent_ptr->add_child(std::make_shared<Node<T>>(std::move(child)));
        } else {
            std::cerr << "Error: Node has reached the maximum number of children.\n";
        }
    } else {
        std::cerr << "Error: Parent node not found in the tree.\n";
    }
}
    


   
    // Pre-order traversal
    PreOrderIterator<T, K> begin_pre_order() const { return PreOrderIterator<T, K>(root); }
    PreOrderIterator<T, K> end_pre_order() const { return PreOrderIterator<T, K>(nullptr); }

    // Post-order traversal
    PostOrderIterator<T, K> begin_post_order() const { return PostOrderIterator<T, K>(root, k == 2); }
    PostOrderIterator<T, K> end_post_order() const { return PostOrderIterator<T, K>(nullptr, k == 2); }

    // In-order traversal (binary tree only)
    InOrderIterator<T, K> begin_in_order() const { return InOrderIterator<T, K>(root, k == 2); }
    InOrderIterator<T, K> end_in_order() const { return InOrderIterator<T, K>(nullptr, k == 2   ); }

    // // BFS traversal
    BFSIterator<T> begin_bfs_scan() const { return BFSIterator<T>(root); }
    BFSIterator<T> end_bfs_scan() const { return BFSIterator<T>(nullptr); }

    // Overloaded begin and end for BFS as default
    BFSIterator<T> begin() const { return begin_bfs_scan(); }
    BFSIterator<T> end() const { return end_bfs_scan(); }


    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
        print_tree(tree.root, os, 0);
        tree.print();
        return os;
    }
    
    BFSIterator<T> myheap() {
    if (!root) return BFSIterator<T>(nullptr);

    std::string beforeString, currentString;
    
    do {
        beforeString = BFSIterator<T>::bfsToString(begin_bfs_scan(), end_bfs_scan());
        heapify(root);
        currentString = BFSIterator<T>::bfsToString(begin_bfs_scan(), end_bfs_scan());
    } while (beforeString != currentString);

    return BFSIterator<T>(root);
}
void delete_tree(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        for (auto& child : node->children) {
            delete_tree(child); // child is already a shared_ptr
        }
}


private:

void heapify(std::shared_ptr<Node<T>>& node) {
        if (!node) return;

        // Recursively heapify the children
        for (auto& child : node->children) {
            heapify(child);
        }

        // Step 2: Maintain min-heap property
        for (auto& child : node->children) {
            if (child && child->value < node->value) {
                std::swap(node->value, child->value);
            }
        }
    }

    
    std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, const T& value) {
        if (!current) return nullptr;
        if (current->value == value) return current;
        for (const auto& child : current->children) {
            auto result = find_node(child, value);
            if (result) return result;
        }
        return nullptr;
    }
    static void print_tree(const std::shared_ptr<Node<T>>& node, std::ostream& os, int depth) {
        if (node) {
            os << std::string(depth * 2, ' ') << node->value << std::endl;
            for (const auto& child : node->children) {
                print_tree(child, os, depth + 1);
            }
        }
    }
};
// The PreOrderIterator traverses a tree in pre-order, 
// using a stack to visit the root node before recursively exploring its children. 
// Traversal: root -> left -> right.
template<typename T, size_t K>
class PreOrderIterator {
public:
    // Constructor that initializes the iterator with the root node of the tree.
    // If the root is not null, it pushes the root node onto the stack to start the traversal.
    PreOrderIterator(const std::shared_ptr<Node<T>>& root) {
        if (root) {
            stack.push(root);
        }
    }

    // Overloaded inequality operator that checks if the current iterator is not equal to another iterator.
    // This is done by checking if either of the stacks (current or other) is not empty.
    bool operator!=(const PreOrderIterator& other) const {
        return !stack.empty() || !other.stack.empty();
    }

    // Overloaded prefix increment operator that moves the iterator to the next node in pre-order.
    // It pops the current node from the stack and pushes its children (in reverse order)
    // to the stack to ensure they are processed in pre-order (root, then left to right).
    PreOrderIterator& operator++() {
        if (!stack.empty()) {
            auto node = stack.top();  // Get the current node
            stack.pop();              // Remove the current node from the stack
            
            // Push the children of the current node onto the stack in reverse order
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);  // Push each child to the stack
            }
        }
        return *this;  // Return the current iterator instance
    }

    // Overloaded dereference operator that returns the current node as a shared pointer.
    // If the stack is empty, it returns nullptr.
    std::shared_ptr<Node<T>> operator*() const {
        return stack.empty() ? nullptr : stack.top();  // Return the top node or nullptr if the stack is empty
    }

    // Overloaded arrow operator that provides access to the current node's members.
    // It returns a raw pointer to the current node, or nullptr if the stack is empty.
    Node<T>* operator->() const {
        return stack.empty() ? nullptr : stack.top().get();  // Return the raw pointer to the current node or nullptr
    }

private:
    // Stack to keep track of the nodes during the traversal.
    std::stack<std::shared_ptr<Node<T>>> stack;
};

// The PostOrderIterator traverses a tree in post-order, 
// managing its traversal using two stacks to ensure children are processed 
// before their parent nodes. 
// Traversal: left -> right -> root.
template<typename T, size_t K>
class PostOrderIterator {
public:
    PostOrderIterator(const std::shared_ptr<Node<T>>& root, bool is_binary) 
        : current(nullptr), is_binary(is_binary) {
        if (root) {
            if (is_binary) {
                pushLeftPath(root);
            } else {
                dfsStack.push(root);
            }
            ++(*this); // Move to the first node
        }
    }

    bool operator!=(const PostOrderIterator& other) const {
        return current != other.current;
    }

    PostOrderIterator& operator++() {
        if (is_binary) {
            if (!stack.empty()) {
                auto node = stack.top();
                stack.pop();
                if (!stack.empty() && stack.top()->children.size() > 1 && node == stack.top()->children[0]) {
                    pushLeftPath(stack.top()->children[1]);
                }
                current = node;
            } else {
                current = nullptr;
            }
        } else {
            if (!dfsStack.empty()) {
                auto node = dfsStack.top();
                dfsStack.pop();
                if (node->children.empty()) {
                    current = node;
                } else {
                    current = nullptr;
                    dfsStack.push(node);
                    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                        dfsStack.push(*it);
                    }
                    ++(*this); // Recurse to find the next leaf
                }
            } else {
                current = nullptr;
            }
        }
        return *this;
    }

    T& operator*() const {
        return current->value;
    }

    Node<T>* operator->() const {
        return current.get();
    }

private:
    std::stack<std::shared_ptr<Node<T>>> stack;
    std::stack<std::shared_ptr<Node<T>>> dfsStack;
    std::shared_ptr<Node<T>> current;
    bool is_binary;

    void pushLeftPath(std::shared_ptr<Node<T>> node) {
        while (node) {
            stack.push(node);
            if (!node->children.empty()) {
                node = node->children[0]; // Assuming binary tree behavior
            } else {
                break;
            }
        }
    }
};



template<typename T, size_t K>
class InOrderIterator {
public:
   
    // The InOrderIterator traverses a binary tree in in-order,
    // visiting the left subtree first, then the root node, and finally the right subtree.
    // Traversal: left -> root -> right.
    InOrderIterator(const std::shared_ptr<Node<T>>& root, bool is_binary) 
        : is_binary(is_binary) {
        if (root) {
            if (is_binary) {
                push_left(root);
            } else {
                stack.push(root);
            }
        }
    }

    bool operator!=(const InOrderIterator& other) const {
        return !stack.empty() || !other.stack.empty();
    }

    InOrderIterator& operator++() {
        if (is_binary) {
            if (!stack.empty()) {
                auto node = stack.top();
                stack.pop();
                if (node->children.size() > 1) {
                    push_left(node->children[1]);
                }
            }
        } else {
            if (!stack.empty()) {
                auto node = stack.top();
                stack.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    stack.push(*it);
                }
            }
        }
        return *this;
    }

    T& operator*() const {
        return stack.top()->value;
    }
    Node<T>* operator->() const {
        return stack.top().get();
    }

private:
    std::stack<std::shared_ptr<Node<T>>> stack;
    bool is_binary;

    void push_left(const std::shared_ptr<Node<T>>& node) {
        auto current = node;
        while (current) {
            stack.push(current);
            if (!current->children.empty()) {
                current = current->children[0];
            } else {
                break;
            }
        }
    }
};
// The BFSIterator traverses a tree using breadth-first search,
// exploring all nodes at the present depth level before moving on to nodes at the next depth level.
// Traversal: level by level, from left to right.

template<typename T>
class BFSIterator {
    // Utility function to print the tree

    
public:
    BFSIterator(const std::shared_ptr<Node<T>>& root) {
        if (root) {
            queue.push(root);
        }
    }
    

    bool operator!=(const BFSIterator& other) const {
        return !queue.empty() || !other.queue.empty();
    }

    BFSIterator& operator++() {
        if (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            for (const auto& child : node->children) {
                queue.push(child);
            }
        }
        return *this;
    }

    std::shared_ptr<Node<T>> operator*() const {
        return queue.empty() ? nullptr : queue.front();
    }

    Node<T>* operator->() const {
        return queue.empty() ? nullptr : queue.front().get();
    }
static std::string bfsToString(BFSIterator<T> begin, BFSIterator<T> end) {
    std::stringstream ss;
    for (auto it = begin; it != end; ++it) {
        ss << (*it)->value << " ";  // Assuming the Node has a 'value' field
    }
    return ss.str();
}


private:
    std::queue<std::shared_ptr<Node<T>>> queue;
};

template<typename T, size_t K>
class DFSIterator {
public:
    DFSIterator(const std::shared_ptr<Node<T>>& root) {
        if (root) {
            stack.push(root);
        }
    }

    bool operator!=(const DFSIterator& other) const {
        return !stack.empty() || !other.stack.empty();
    }

    DFSIterator& operator++() {
        if (!stack.empty()) {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
        }
        return *this;
    }

    std::shared_ptr<Node<T>> operator*() const {
        return stack.empty() ? nullptr : stack.top();
    }

    Node<T>* operator->() const {
        return stack.empty() ? nullptr : stack.top().get();
    }

private:
    std::stack<std::shared_ptr<Node<T>>> stack;
};

// The Heap is a specialized tree-based data structure that satisfies the heap property,
// where each parent node is either greater than (max heap) or less than (min heap) its children.

template<typename T>
class HeapIterator {
public:
    HeapIterator(const std::shared_ptr<Node<T>>& root) {
        if (root) {
            queue.push(root);
        }
    }

    bool operator!=(const HeapIterator& other) const {
        return !queue.empty() || !other.queue.empty();
    }

    HeapIterator& operator++() {
        if (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            for (const auto& child : node->children) {
                queue.push(child);
            }
        }
        return *this;
    }

    std::shared_ptr<Node<T>> operator*() const {
        return queue.empty() ? nullptr : queue.front();
    }

    Node<T>* operator->() const {
        return queue.empty() ? nullptr : queue.front().get();
    }

private:
    std::queue<std::shared_ptr<Node<T>>> queue;
};








#endif // TREE_HPP
