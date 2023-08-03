#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;

#include <bits/stdc++.h>
#include <list>
#include <string>

struct PlayerData {
  unsigned int identifier;
  string name;
  string positions;
  double rating;
  unsigned int count;
};

struct RatingData {
  unsigned int player_id;
  unsigned int user_id;
  float rating;
};

template <typename T> class Bucket {
public:
  unsigned int key;
  T value;

  Bucket(unsigned int key, T value) {
    this->key = key;
    this->value = value;
  }
};

enum BucketState { EMPTY, TOMBSTONE, FILLED };

template <typename T> class HashTable {
private:
  Bucket<T> **table = nullptr;
  unsigned int buckets;
  list<unsigned int> keys;
  unsigned int table_owner;
  unsigned int hash_code(unsigned int identifier) {
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
  unsigned int probe(unsigned int identifier, unsigned short n) {
    return (hash_code(identifier) + (n * n + n) / 2) % buckets;
  }

public:
  HashTable(unsigned int bucket_count) {
    this->buckets = bucket_count;
    table = new Bucket<T> *[buckets];
  }

  HashTable(unsigned int bucket_count, unsigned int table_owner) {
    this->buckets = bucket_count;
    table = new Bucket<T> *[buckets];
    this->table_owner = table_owner;
  }

  unsigned int get_table_owner() { return table_owner; }

  void insert(unsigned int identifier, T data) {
    unsigned int n = 0, index = 0, count = 0;
    while (table[index = probe(identifier, n++)])
      if (n == buckets)
        return;
    keys.push_back(identifier);

    Bucket<T> *bucket = new Bucket<T>(identifier, data);
    table[index] = bucket;
  }

  T *search(unsigned int identifier) {
    unsigned int n = 0, index = 0;
    while (table[index = probe(identifier, n++)]) {
      if (table[index]->key == identifier)
        return &table[index]->value;
      if (n == buckets)
        return nullptr;
    }
    return nullptr;
  }

  bool contains(unsigned int identifier) {
    return search(identifier) != nullptr;
  }

  list<unsigned int> &keySet() { return keys; }
};
#endif
