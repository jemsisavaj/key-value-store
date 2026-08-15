#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <chrono>
#include "../include/kv_store.hpp"

using namespace std;

void cleanupTestFile() {
    remove("test_data.dat");
}

void testBasicOperations(){
    cout << "[TEST 1] Running Basic Operations Test" << endl;
    KeyValueStore store("test_data.dat");

    store.put("key1", "val1");
    store.put("key2", "val2");

    assert(store.get("key1") == "val1");
    assert(store.get("key2") == "val2");

    store.del("key1");
    assert(store.get("key1") == "NOT_FOUND");

    cout << "  --> PASSED!\n" << endl;
    cleanupTestFile();
}

void testTTLExpiration(){
    cleanupTestFile();
    cout << "[TEST 2] Running TTL & Expiration Test..." << endl;
    
    KeyValueStore store("test_data.dat");

    store.put("expiring_key", "temp_data", 2);
    assert(store.get("expiring_key") == "temp_data");

    cout << "  Waiting 3 seconds for key to expire..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    string res = store.get("expiring_key");
    assert(res == "NOT_FOUND (EXPIRED)" || res == "NOT_FOUND");

    cout << "  --> TEST 2 PASSED!\n" << endl;
    cleanupTestFile();
}

void testConcurrency(){
    cleanupTestFile();
    cout << "[TEST 3] Running Multi-threaded Concurrency Stress Test..." << endl;
    
    KeyValueStore store("test_data.dat");
    
    const int numThreads = 10;
    const int keysPerThread = 50;
    vector<thread> workers;

    for(int t=0; t<numThreads; ++t){
        workers.emplace_back([&store, t, keysPerThread](){
            for(int i=0; i<keysPerThread; ++i){
                string k = "thread_" + to_string(t) + "_key_" + to_string(i);
                string v = "val_" + to_string(i);
                store.put(k, v);
            }
        });
    }

    for(auto& th : workers){
        th.join();
    }

    for(int t=0; t<numThreads; ++t){
        for(int i=0; i<keysPerThread; ++i){
            string k = "thread_" + to_string(t) + "_key_" + to_string(i);
            string v = "val_" + to_string(i);
            assert(store.get(k) == v);
        }
    }
    cout << "  --> PASSED! Successfully handled " << (numThreads * keysPerThread) << " parallel writes without race condition.\n" << endl;
    cleanupTestFile();
}

void testCompaction(){
    cleanupTestFile();
    cout << "[TEST 4] Running Compaction Clean-up Test" << endl;
    KeyValueStore store("test_data.dat");

    store.put("cleanKey1", "100");
    store.put("cleanKey2", "200");
    store.del("cleanKey1");

    store.compact();

    assert(store.get("cleanKey2") == "200");
    assert(store.get("cleanKey1") == "NOT_FOUND");

    cout << "  --> PASSED!\n" << endl;
    cleanupTestFile();
}

int main(){
    cout << "========================================" << endl;
    cout << "  STARTING AUTOMATED SYSTEM UNIT TESTS  " << endl;
    cout << "========================================" << endl;

    testBasicOperations();
    testTTLExpiration();
    testConcurrency();
    testCompaction();

    cout << "==========================================" << endl;
    cout << "  ALL 4 SYSTEM TESTS PASSED SUCCESSFULLY! " << endl;
    cout << "==========================================" << endl;

    return 0;
}