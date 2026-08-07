#ifndef KV_STORE_HPP
#define KV_STORE_HPP

#include "hash_index.hpp"
#include "file_handler.hpp"

using namespace std;

class KeyValueStore {
private:
    HashIndex memoryStore;
    FileHandler diskStore;

public:
    KeyValueStore(const string& filename);

    void put(const string& key, const string& value);
    string get(const string& key);
    void del(const string& key);
    void compact();
};

#endif