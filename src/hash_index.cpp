#include "../include/hash_index.hpp"

HashIndex::HashIndex(){
    cleanupThread = thread([this](){
        while(!stopThread){
            this_thread::sleep_for(chrono::seconds(5));
            this->cleanupExpiredKeys();
        }
    });
}

HashIndex::~HashIndex(){
    stopThread = true;
    if(cleanupThread.joinable()){
        cleanupThread.join();
    }
}

void HashIndex::cleanupExpiredKeys(){
    lock_guard<mutex> lock(mtx);
    auto now = chrono::steady_clock::now();
    int count = 0;

    for(auto it = expiryStore.begin(); it != expiryStore.end(); ){
        if(now > it->second){
            store.erase(it->first);
            it = expiryStore.erase(it);
            count++;
        }
        else{
            ++it;
        }
    }
    if(count > 0){
        cout << "\n[Background clear] Automatically cleaned " << count << " expired keys from memory!" << endl;
    }
}

void HashIndex::put(string key, string value, int ttlInSeconds){
    lock_guard<mutex> lock(mtx);
    store[key] = value;

    if(ttlInSeconds > 0){
        expiryStore[key] == chrono::steady_clock::now() + chrono::seconds(ttlInSeconds);
    }
    else{
        expiryStore.erase(key);
    }
}

string HashIndex::get(string key){
    lock_guard<mutex> lock(mtx);
    
    if(store.find(key) == store.end()){
        return "Key not found";
    }

    if(expiryStore.find(key) != expiryStore.end()){
        if(chrono::steady_clock::now() > expiryStore[key]){
            store.erase(key);
            expiryStore.erase(key);
            return "NOT_FOUND (Expired)";
        }
    }
    return store[key];
}

void HashIndex::del(string key){
    lock_guard<mutex> lock(mtx);
    store.erase(key);
    expiryStore.erase(key);
}

vector<pair<string, string>> HashIndex::getAll(){
    lock_guard<mutex> lock(mtx);
    vector<pair<string, string>> allData;
    auto now = chrono::steady_clock::now();

    for(const auto& pair : store){
        if(expiryStore.find(pair.first) == expiryStore.end() || now<= expiryStore[pair.first]){
            allData.push_back(pair);
        }
    }
    return allData;
}