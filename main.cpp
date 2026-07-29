#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class KeyValueStore{
private :
    unordered_map<string,string> store;
    
public :
    void set(string key,string value){
        store[key] = value;
        cout << "OK : Saved (" << key << "->" << value << ")" << endl;
    }

    void get(string key){
        if(store.find(key) != store.end()){
            cout << "Value : " << store[key] << endl;
        } 
        else{
            cout << "Value is not found" << endl;
        }
    }

    void dlt(string key){
        if(store.erase(key)){
            cout << "OK! Deleted Key : " << key << endl;
        }
        else{
            cout << "Key is not found" << endl;
        }
    }
};

int main(){
    KeyValueStore kv;

    kv.set("Jemsi","IITRAM");
    kv.set("Maitri","PDPU");

    kv.get("Maitri");
    kv.dlt("Jemsi");
    kv.dlt("RAM");

    return 0;
}