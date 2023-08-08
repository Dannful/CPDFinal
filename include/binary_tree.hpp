#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <bits/stdc++.h>

using namespace std;

template<typename K, typename V>
class BinaryTreeNode {
public:
    BinaryTreeNode<K, V> *left, *right;
    K key;
    V value;

    BinaryTreeNode(K key, V value) {
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

template<typename K, typename V>
class BinarySearchTree {
private:
    function<double(K, K)> compare;

    BinaryTreeNode<K, V> *root = nullptr;

    BinaryTreeNode<K, V> *insert(BinaryTreeNode<K, V> *node, K key, V value) {
        if (!node)
            return new BinaryTreeNode<K, V>(key, value);
        if (compare(node->key, key) > 0)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);
        return node;
    }

    void
    inorder_traverse(unsigned int *count, unsigned int max, BinaryTreeNode<K, V> *node,
                     const function<void(K, V)> &on_element) {
        if (!node)
            return;
        inorder_traverse(count, max, node->right, on_element);
        if ((*count)++ >= max)
            return;
        on_element(node->key, node->value);
        inorder_traverse(count, max, node->left, on_element);
    }

public:

    explicit BinarySearchTree<K, V>(const function<double(K, K)> &compare) {
        this->compare = compare;
    }

    void insert(K key, V value) {
        root = insert(root, key, value);
    }

    void inorder_traverse(unsigned int count,
                          const function<void(K, V)> &on_element) {
        unsigned int visited = 0;
        inorder_traverse(&visited, count, root, on_element);
    }

    bool contains(K key) {
        BinaryTreeNode<K, V> *node = root;
        while(node) {
            if(compare(node->key, key) == 0)
                return true;
            if(compare(node->key, key) > 0)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }
};

#endif