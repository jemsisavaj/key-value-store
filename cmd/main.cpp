#include <iostream>
#include "../include/hash_index.hpp"
#include "../include/file_handler.hpp"

int main(){
    HashIndex memoryStore;
    FileHandler diskStore("data.dat");

    auto saveRecords = diskStore.readAllRecords();
    for(const auto& record : saveRecords){
        memoryStore.put(record.first, record.second);
    }

    cout << "Loaded " << saveRecords.size() << " records from file to memory!" << endl;

    string key = "course";
    string value = "BTech_computer";

    memoryStore.put(key, value);
    diskStore.appendRecord(key, value);

    cout << "GET course from Memory : " << memoryStore.get("course") << endl; 

    return 0;
}