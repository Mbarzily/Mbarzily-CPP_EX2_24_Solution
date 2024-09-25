// matanayabarzilay@gmail.com
#include "tree.cpp"
#include "Complex.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// Explicit template instantiation


void printTree(const Tree<Complex>& tree, const std::string& traversalType) {
    std::cout << "Tree " << traversalType << " traversal:" << std::endl;
    if (traversalType == "BFS") {
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            std::cout << (*it)->value << " ";
        }
    } else if (traversalType == "Pre-order") {
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            std::cout << (*it)->value << " ";
        }
    // } else if (traversalType == "Post-order") {
    //     for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
    //         std::cout << (it)->value << " ";
    //     }
    } else if (traversalType == "In-order") {
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            std::cout << (it)->value << " ";
        }
    
    }
    std::cout << std::endl << std::endl;
}

int main() {
    // Create a binary tree
    Node<Complex> root(Complex(3, 3));
    Node<Complex> n1(Complex(7, 7));
    Node<Complex> n2(Complex(9, 9));
    Node<Complex> n3(Complex(4, 4));
    Node<Complex> n4(Complex(5, 5));
    Node<Complex> n5(Complex(7, 3));
    Node<Complex> n6(Complex(5, 7));
    Node<Complex> n7(Complex(8, 9));
    Node<Complex> n8(Complex(2, 4));
    Node<Complex> n9(Complex(1, 5));
    Node<Complex> n10(Complex(7, 7));
    Node<Complex> n11(Complex(9, 9));
    Node<Complex> n12(Complex(4, 4));
    Node<Complex> n13(Complex(5, 5));
    Node<Complex> n14(Complex(7, 3));
    Tree<Complex> binaryTree(3);
    binaryTree.add_root(root);
    binaryTree.add_sub_node(root,n1);
    binaryTree.add_sub_node(root,n2);
    binaryTree.add_sub_node(root,n3);
    binaryTree.add_sub_node(root,n4);
    binaryTree.add_sub_node(n1,n5);
    binaryTree.add_sub_node(n1,n6);
    binaryTree.add_sub_node(n1,n7);
    binaryTree.add_sub_node(n2,n8);
    binaryTree.add_sub_node(n2,n9);
    binaryTree.add_sub_node(n3,n11);
    binaryTree.add_sub_node(n3,n12);
    binaryTree.add_sub_node(n3,n13);
    
    std::cout << "Original Binary Tree:" << std::endl;
    std::cout << binaryTree << std::endl;
    printTree(binaryTree, "BFS");
  
    // Convert tree to heap
    binaryTree.treeToHeap();

    std::cout << "Binary Tree after conversion to Heap:" << std::endl;
    std::cout << binaryTree << std::endl;

    // Display heap
    binaryTree.print();

    // Demonstrate Complex class operations
    Complex c1(1, 2);
    Complex c2(3, 4);
    
    std::cout << "Complex number operations:" << std::endl;
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c1++ = " << c1++ << std::endl;
    std::cout << "c1 after postfix++ = " << c1 << std::endl;
    std::cout << "c1 < c2 : " << (c1 < c2) << std::endl;
    std::cout << "c1 > c2 : " << (c1 > c2) << std::endl;
    std::cout << "c1 == c2 : " << (c1 == c2) << std::endl;
    std::cout << "c1 != c2 : " << (c1 != c2) << std::endl;

    return 0;
}