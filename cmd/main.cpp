#include <iostream>
#include "../include/kv_store.hpp"
using namespace std;

int main(){
    KeyValueStore store("data.dat");

    store.put("role", "Developer");
    store.put("city", "Ahmedabad");

    cout << "GET role: " << store.get("role") << endl;
    cout << "GET city: " << store.get("city") << endl;

    store.del("role");
    store.compact();

    cout << "GET role (after delete): " << store.get("role") << endl;

    return 0;
}