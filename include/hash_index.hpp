#ifndef HASH_INDEX_HPP
#define HASH_INDEX_HPP

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class HashIndex {
private:
    unordered_map<string, string> store;

public:
    void put(string key, string value);
    string get(string key);
    void del(string key);
};

#endif