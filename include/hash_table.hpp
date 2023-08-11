#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;

#include <bits/stdc++.h>
#include <list>
#include <string>
#include "binary_tree.hpp"

unsigned int hash_int(unsigned int identifier) {
    constexpr uint64_t BIT_NOISE1 = 0x9E3779B185EBCA87ULL;
    constexpr uint64_t BIT_NOISE2 = 0xC2B2AE3D27D4EB4FULL;
    constexpr uint64_t BIT_NOISE3 = 0x27D4EB2F165667C5ULL;
    identifier *= BIT_NOISE1;
    identifier ^= (identifier >> 8);
    identifier += BIT_NOISE2;
    identifier ^= (identifier << 8);
    identifier *= BIT_NOISE3;
    identifier ^= (identifier >> 8);
    return identifier;
}

unsigned int hash_string(string s) {
    unsigned int hash = 5381;
    char character;
    unsigned int character_position = 0;
    unsigned int length = s.length();

    while (character_position < length && (character = s.at(character_position++)))
        hash = ((hash << 5) + hash) + character;
    return hash;
}

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
