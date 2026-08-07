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

    memoryStore.put("tempKey", "to_be_deleted");
    diskStore.appendRecord("tempKey", "to_be_deleted");

    memoryStore.put("name", "Jemsi");
    diskStore.appendRecord("name", "Jemsi");

    memoryStore.del("tempKey");

    cout << "Running Compaction..." << endl;
    diskStore.rewriteAllRecords(memoryStore.getAll());
    cout << "Compaction Done! Clean data saved to file." << endl;

    return 0;
}