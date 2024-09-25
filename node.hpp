// matanayabarzilay@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <iostream>
#include <string>   

template<typename T>

class Node {
public:
    T value;
    std::vector<std::shared_ptr<Node<T>>> children;

    Node(T val) : value(std::move(val)) {}

     T get_value(){
        return this->value;
    }
    void add_child(std::shared_ptr<Node<T>> child) {
        children.push_back(std::move(child));
    }
};

#endif