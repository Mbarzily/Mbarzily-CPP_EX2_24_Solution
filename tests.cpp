// matanayabarzilay@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.cpp"
#include "Complex.hpp"
#include <sstream>

// Helper function to get traversal as string
template<typename Iterator>
std::string getTraversalString(Iterator begin, Iterator end) {
    std::stringstream ss;
    for (auto it = begin; it != end; ++it) {
        ss << (it)->value << " ";
    }
    return ss.str();
}

TEST_CASE("Tree operations and traversals") {
    SUBCASE("Empty tree") {
        Tree<Complex> emptyTree;
        CHECK(getTraversalString(emptyTree.begin_bfs_scan(), emptyTree.end_bfs_scan()) == "");
    }

    SUBCASE("Tree with only root") {
        Tree<Complex> rootOnlyTree(2);
        Node<Complex> root(Complex(1, 1));
        rootOnlyTree.add_root(root);

        CHECK(getTraversalString(rootOnlyTree.begin_bfs_scan(), rootOnlyTree.end_bfs_scan()) == "1+1i ");
        CHECK(getTraversalString(rootOnlyTree.begin_pre_order(), rootOnlyTree.end_pre_order()) == "1+1i ");
        CHECK(getTraversalString(rootOnlyTree.begin_post_order(), rootOnlyTree.end_post_order()) == "1+1i ");
        CHECK(getTraversalString(rootOnlyTree.begin_in_order(), rootOnlyTree.end_in_order()) == "1+1i ");
    }

    SUBCASE("Full binary tree") {
        Tree<Complex> fullTree(2);
        Node<Complex> root(Complex(1, 1)), n1(Complex(2, 2)), n2(Complex(3, 3)), n3(Complex(4, 4)), n4(Complex(5, 5));
        fullTree.add_root(root);
        fullTree.add_sub_node(root, n1);
        fullTree.add_sub_node(root, n2);
        fullTree.add_sub_node(n1, n3);
        fullTree.add_sub_node(n1, n4);

        CHECK(getTraversalString(fullTree.begin_bfs_scan(), fullTree.end_bfs_scan()) == "1+1i 2+2i 3+3i 4+4i 5+5i ");
        CHECK(getTraversalString(fullTree.begin_pre_order(), fullTree.end_pre_order()) == "1+1i 2+2i 4+4i 5+5i 3+3i ");
        CHECK(getTraversalString(fullTree.begin_post_order(), fullTree.end_post_order()) == "4+4i 5+5i 2+2i 3+3i 1+1i ");
        CHECK(getTraversalString(fullTree.begin_in_order(), fullTree.end_in_order()) == "4+4i 2+2i 5+5i 1+1i 3+3i ");
    }

    SUBCASE("Skewed tree (left)") {
        Tree<Complex> skewedTree(2);
        Node<Complex> root(Complex(1, 1)), n1(Complex(2, 2)), n2(Complex(3, 3)), n3(Complex(4, 4));
        skewedTree.add_root(root);
        skewedTree.add_sub_node(root, n1);
        skewedTree.add_sub_node(n1, n2);
        skewedTree.add_sub_node(n2, n3);

        CHECK(getTraversalString(skewedTree.begin_bfs_scan(), skewedTree.end_bfs_scan()) == "1+1i 2+2i 3+3i 4+4i ");
        CHECK(getTraversalString(skewedTree.begin_pre_order(), skewedTree.end_pre_order()) == "1+1i 2+2i 3+3i 4+4i ");
        CHECK(getTraversalString(skewedTree.begin_post_order(), skewedTree.end_post_order()) == "4+4i 3+3i 2+2i 1+1i ");
        CHECK(getTraversalString(skewedTree.begin_in_order(), skewedTree.end_in_order()) == "4+4i 3+3i 2+2i 1+1i ");
    }

    SUBCASE("3-ary tree") {
        Tree<Complex> threeAryTree(3);
        Node<Complex> root(Complex(1, 1)), n1(Complex(2, 2)), n2(Complex(3, 3)), n3(Complex(4, 4)),
                           n4(Complex(5, 5)), n5(Complex(6, 6)), n6(Complex(7, 7)), n7(Complex(8, 8));
        threeAryTree.add_root(root);
        threeAryTree.add_sub_node(root, n1);
        threeAryTree.add_sub_node(root, n2);
        threeAryTree.add_sub_node(root, n3);
        threeAryTree.add_sub_node(n1, n4);
        threeAryTree.add_sub_node(n1, n5);
        threeAryTree.add_sub_node(n1, n6);
        threeAryTree.add_sub_node(n2, n7);

        CHECK(getTraversalString(threeAryTree.begin_bfs_scan(), threeAryTree.end_bfs_scan()) == "1+1i 2+2i 3+3i 4+4i 5+5i 6+6i 7+7i 8+8i ");
        CHECK(getTraversalString(threeAryTree.begin_pre_order(), threeAryTree.end_pre_order()) == "1+1i 2+2i 5+5i 6+6i 7+7i 3+3i 8+8i 4+4i ");
        CHECK(getTraversalString(threeAryTree.begin_in_order(), threeAryTree.end_in_order()) == "1+1i 2+2i 5+5i 6+6i 7+7i 3+3i 8+8i 4+4i ");
    }
}

TEST_CASE("treeToHeap conversion") {
    Tree<Complex> heapTree(2);
    Node<Complex> root(Complex(5, 5)), n1(Complex(4, 4)), n2(Complex(2, 2)), n3(Complex(3, 3)), n4(Complex(1, 1));
    heapTree.add_root(root);
    heapTree.add_sub_node(root, n1);
    heapTree.add_sub_node(root, n2);
    heapTree.add_sub_node(n1, n3);
    heapTree.add_sub_node(n1, n4);

    std::string beforeHeap = getTraversalString(heapTree.begin_bfs_scan(), heapTree.end_bfs_scan());
    std::cout << "Before heap: " << beforeHeap << std::endl;

    heapTree.myheap();
    std::string afterHeap = getTraversalString(heapTree.begin_bfs_scan(), heapTree.end_bfs_scan());
    std::cout << "After heap: " << afterHeap << std::endl;
    CHECK(beforeHeap != afterHeap);
    CHECK(afterHeap == "1+1i 3+3i 2+2i 5+5i 4+4i ");
}


TEST_CASE("Complex class operations") {
    
    Complex c1(1, 2), c2(3, 4);

    SUBCASE("Addition") {
        CHECK(c1 + c2 == Complex(4, 6));
    }

    SUBCASE("Subtraction") {
        CHECK(c1 - c2 == Complex(-2, -2));
    }

    SUBCASE("Multiplication") {
        CHECK(c1 * c2 == Complex(-5, 10));
    }

    SUBCASE("Prefix increment") {
        Complex c = c1;
        CHECK(++c == Complex(2, 2));
        CHECK(c == Complex(2, 2));
    }

    SUBCASE("Postfix increment") {
        Complex c = c1;
        CHECK(c++ == Complex(1, 2));
        CHECK(c == Complex(2, 2));
    }

    SUBCASE("Comparisons") {
        CHECK(c1 < c2);
        CHECK_FALSE(c1 > c2);
        CHECK_FALSE(c1 == c2);
        CHECK(c1 != c2);
    }
}