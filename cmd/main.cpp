#include <iostream>
#include <sstream>
#include <string>
#include "../include/kv_store.hpp"
using namespace std;

int main(){
    KeyValueStore store("data.dat");

    cout << "     Welcome to C++ Key-Value Store CLI     " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Available Commands: " << endl;
    cout << " SET <key> <value> - Save a key-value pair" << endl;
    cout << " GET <key> - Rewrite value by key" << endl;
    cout << " DEL <key> - Delete key from store" << endl;
    cout << " COMPACT - Clean up storage file" << endl;
    cout << " EXIT - Exit the program" << endl;
    
    string input;
    while(true){
        cout << "\nkvstore> ";
        if(!getline(cin, input) || input == "EXIT"){
            cout << "Exiting key-value store" << endl;
            break;
        }

        stringstream ss(input);
        string command, key, value;
        ss >> command;

        if(command == "SET"){
            if(ss >> key >> value){
                store.put(key, value);
                cout << "SUCCESS: [ " << key << " -> " << value << " ] saved!" << endl; 
            }
            else{
                cout << "ERROR: Invalid uage! Syntax: SET <key> <value>" << endl;
            }
        }
        else if(command == "GET"){
            if(ss >> key){
                cout << "VALUE: " << store.get(key) << endl;
            }
            else{
                cout << "ERROR: Invalid usage! Syntax: GET <key>" << endl;
            }
        }
        else if(command == "DEL"){
            if(ss >> key){
                store.del(key);
                cout << "SUCCESS: Key " << key << " deleted!" << endl;
            }
            else{
                cout << "ERROR: Invalid usage! Syntax: DEL <key>" << endl; 
            }
        }
        else if(command == "COMPACT"){
            store.compact();
            cout << "SUCCESS: Storage file compaction completed!" << endl;
        }
        else if(!command.empty()){
            cout << "ERROR: Unknown command '"<< command << "'!" << endl;
        }
    }

    return 0;
}