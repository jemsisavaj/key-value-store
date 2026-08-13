#include "../include/kv_store.hpp"

using namespace std;

KeyValueStore::KeyValueStore(const string& filename) : diskStore(filename){
    auto records = diskStore.readAllRecords();
    for(const auto& pair : records){
        memoryStore.put(pair.first, pair.second);
    }
}

void KeyValueStore::put(const string& key, const string& value, int ttlInSeconds){
    memoryStore.put(key, value, ttlInSeconds);
    diskStore.appendRecord(key, value);
}

string KeyValueStore::get(const string& key){
    return memoryStore.get(key);
}

void KeyValueStore::del(const string& key){
    memoryStore.del(key);
}

void KeyValueStore::compact(){
    diskStore.rewriteAllRecords(memoryStore.getAll());
}