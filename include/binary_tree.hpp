#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <bits/stdc++.h>

using namespace std;

struct PlayerWithTag {
    unsigned int identifier;
    string tag;
};

struct PlayerWithRating {
    unsigned int identifier;
    double rating;
};

template<typename T>
class BinaryTreeNode {
public:
    BinaryTreeNode<T> *left, *right;
    T value;

    BinaryTreeNode(T value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class BinarySearchTree {
private:
    function<double(T, T)> compare;

    BinaryTreeNode<T> *root = nullptr;

    BinaryTreeNode<T> *insert(BinaryTreeNode<T> *node, T value) {
        if (!node)
            return new BinaryTreeNode<T>(value);
        if (compare(node->value, value) > 0)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    void
    inorder_traverse(unsigned int *count, unsigned int max, BinaryTreeNode<T> *node,
                     const function<void(T)> &on_element) {
        if (!node)
            return;
        inorder_traverse(count, max, node->right, on_element);
        if ((*count)++ >= max)
            return;
        on_element(node->value);
        inorder_traverse(count, max, node->left, on_element);
    }

public:

    explicit BinarySearchTree<T>(const function<double(T, T)> &compare) {
        this->compare = compare;
    }

    void insert(T value) {
        root = insert(root, value);
    }

    void inorder_traverse(unsigned int count,
                          const function<void(T)> &on_element) {
        unsigned int visited = 0;
        inorder_traverse(&visited, count, root, on_element);
    }

    bool contains(T value) {
        BinaryTreeNode<T> *node = root;
        while(node) {
            if(compare(node->value, value) == 0)
                return true;
            if(compare(node->value, value) > 0)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }
};

#endif