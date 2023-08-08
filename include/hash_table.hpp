#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;

#include <bits/stdc++.h>
#include <list>
#include <string>
#include "binary_tree.hpp"

template<typename K, typename V>
class Bucket {
public:
    K key;
    V value;

    Bucket(K key, V value) {
        this->key = key;
        this->value = value;
    }
};

template<typename K, typename V>
class HashTable {
private:
    Bucket<K, V> **table = nullptr;
    unsigned int buckets;
    list<K> keys;
    function<unsigned int(K)> hash_function;

    unsigned int probe(K key, unsigned short n) const {
        return (hash_function(key) + (n * n + n) / 2) % buckets;
    }

public:
    explicit HashTable(unsigned int bucket_count, const function<unsigned int(K)>& hash_function) {
        this->buckets = bucket_count;
        this->hash_function = hash_function;
        table = new Bucket<K, V> *[buckets]();
    }

    void insert(K key, V value) {
        unsigned int n = 0, index;
        while (table[index = probe(key, n++)])
            if (n == buckets)
                return;
        keys.push_back(key);

        auto *bucket = new Bucket<K, V>(key, value);
        table[index] = bucket;
    }

    V *search (K key) const {
        unsigned int n = 0, index;
        while (table[index = probe(key, n++)]) {
            if (table[index]->key == key)
                return &table[index]->value;
            if (n == buckets)
                return nullptr;
        }
        return nullptr;
    }

    [[nodiscard]] list<unsigned int> keySet() const { return keys; }
};

struct PlayerData {
    unsigned int identifier;
    string name;
    string positions;
    BinarySearchTree<string, short> *tags;
    double rating;
    unsigned int count;
};

#endif
