#ifndef FILE_HANDLET_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <utility>
#include <vector>
using namespace std;

class FileHandler{
private:
    string filePath;
    ofstream writeStream;
    mutex mtx;

public:
    FileHandler(const string& filename);
    ~FileHandler();

    bool appendRecord(const string& key, const string& value);

    vector<pair<string,string>> readAllRecords();

    bool rewriteAllRecords(const vector<pair<string, string>>& records);
};

#endif
