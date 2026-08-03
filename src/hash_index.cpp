#include "../include/hash_index.hpp"

void HashIndex::put(string key, string value){
    lock_guard<mutex> lock(mtx);
    store[key] = value;
}

string HashIndex::get(string key){
    lock_guard<mutex> lock(mtx);
    if(store.find(key) != store.end()){
        return store[key];
    }
    return "Key not found";
}

void HashIndex::del(string key){
    lock_guard<mutex> lock(mtx);
    store.erase(key);
}