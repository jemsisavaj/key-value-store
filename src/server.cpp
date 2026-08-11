#include "../include/server.hpp"
#include <sstream>

using namespace std;

Server::Server(int p, KeyValueStore& kvs) : port(p), store(kvs) {}

void Server::start(){
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

//make socket
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFd < 0){
        cout << "ERROR: Socket creation failed!" << endl;
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

//connect
    if(bind(serverFd, (struct sockaddr*)&address, sizeof(address))<0 ){
        cout << "ERROR: Bind failed on port " << port << endl;
        return;
    }

//listen
    if(listen(serverFd, 3) < 0){
        cout << "ERROR: Listen failed!" << endl;
        return;
    }

    cout << "========================================" << endl;
    cout << "       Server Listening on port         " << endl;
    cout << "========================================" << endl;

while(true){
#ifdef _WIN32
    int addrlen = sizeof(address);
    int newSocket = accept(serverFd, (struct sockaddr*)&address, &addrlen);
#else
    socklen_t addrlen = sizeof(address);
    int newSocket = accept(serverFd, (struct sockaddr*)&address, &addrlen);
#endif
    if (newSocket >= 0) {
        cout << "Client connected successfully!" << endl;
        char buffer[1024] = {0};
    

#ifdef _WIN32
        recv(newSocket, buffer, 1024, 0);
#else
        read(newSocket, buffer, 1024);
#endif

        string input(buffer);
        stringstream ss(input);
        string command, key, value, response;

        ss >> command;

        if (command == "GET" && ss >> key) {
            response = store.get(key) + "\n";
        } 
        else if (command == "SET" && ss >> key >> value) {
            store.put(key, value);
            response = "OK\n";
        } 
        else {
            response = "UNKNOWN_COMMAND\n";
        }

        send(newSocket, response.c_str(), response.length(), 0);

#ifdef _WIN32
            closesocket(newSocket);
#else
            close(newSocket);
#endif
        }
    }

#ifdef _WIN32
    closesocket(serverFd);
    WSACleanup();
#else
    close(serverFd);
#endif
}

    
    