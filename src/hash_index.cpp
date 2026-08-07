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

vector<pair<string, string>> HashIndex::getAll(){
    lock_guard<mutex> lock(mtx);
    vector<pair<string, string>> allData;
    for(const auto& pair : store){
        allData.push_back(pair);
    }
    return allData;
}