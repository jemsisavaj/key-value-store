#include <iostream>
#include "../include/hash_index.hpp"

int main(){
    HashIndex mystore;

    mystore.put("name", "jemsi");

    cout << "Name : " << mystore.get("name") << endl;

    mystore.del("name");
    cout << "After Delete: " << mystore.get("name") << endl;

    return 0;
}