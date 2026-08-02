#include "../include/hash_index.hpp"

void HashIndex::put(string key, string value){
    store[key] = value;
}

string HashIndex::get(string key){
    if(store.find(key) != store.end()){
        return store[key];
    }
    return "Key not found";
}

void HashIndex::del(string key){
    store.erase(key);
}