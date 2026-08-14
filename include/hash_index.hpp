#ifndef HASH_INDEX_HPP
#define HASH_INDEX_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <mutex>
#include <chrono>
#include <thread>
#include <atomic>
using namespace std;

class HashIndex {
private:
    unordered_map<string, string> store;
    unordered_map<string, chrono::steady_clock::time_point> expiryStore;
    mutable mutex mtx;

    //active cleanup-variable
    atomic<bool> stopThread{false};
    thread cleanupThread;

    void cleanupExpiredKeys();

public:
    HashIndex();
    ~HashIndex();
    
    void put(string key, string value, int ttlInSeconds = 0);
    string get(string key);
    void del(string key);
    

    vector<pair<string, string>> getAll();
};

#endif