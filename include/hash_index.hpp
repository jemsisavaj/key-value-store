#ifndef HASH_INDEX_HPP
#define HASH_INDEX_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <mutex>
using namespace std;

class HashIndex {
private:
    unordered_map<string, string> store;
    unordered_map<string, chrono::steady_clock::time_point> expiryStore;
    mutable mutex mtx;

public:
    void put(string key, string value, int ttlInSeconds = 0);
    string get(string key);
    void del(string key);
    

    vector<pair<string, string>> getAll();
};

#endif