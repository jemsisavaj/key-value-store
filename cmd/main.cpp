#include <iostream>
#include "../include/hash_index.hpp"
#include "../include/file_handler.hpp"

int main(){
    HashIndex mystore;
    FileHandler diskStore("data.dat");

    string key = "user";
    string value = "Jemsi";

    mystore.put(key, value);

    if(diskStore.appendRecord(key,value)){
        cout << "Data saved to memory and written to file (data.dat)!" << endl;
    }

    cout << "GET from Memory : " << mystore.get(key) << endl; 

    return 0;
}