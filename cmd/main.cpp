#include <iostream>
#include "../include/kv_store.hpp"
#include "../include/server.hpp"
using namespace std;

int main(){
    KeyValueStore store("data.dat");

    Server server(8080, store);
    server.start();

    return 0;
}