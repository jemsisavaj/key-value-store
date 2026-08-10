#ifndef SERVER_HPP
#define SERVER_HPP

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif

#include <iostream>
#include <string>
#include "kv_store.hpp"

class Server {
private:
    int port;
    KeyValueStore& store;

public:
    Server(int p, KeyValueStore& kvs);
    void start();
};

#endif