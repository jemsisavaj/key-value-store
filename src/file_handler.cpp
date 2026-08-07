#include "../include/file_handler.hpp"
#include <sstream>

FileHandler::FileHandler(const string& filename) : filePath(filename){
    writeStream.open(filePath, ios::out | ios::app);
}

FileHandler::~FileHandler(){
    if(writeStream.is_open()){
        writeStream.close();
    }
}

bool FileHandler::appendRecord(const string& key, const string& value){
    lock_guard<mutex> lock(mtx);

    if(!writeStream.is_open()){
        return false;
    }

    writeStream << key << "|" << value << "\n";
    writeStream.flush();
    return true;
}

vector<pair<string,string>> FileHandler::readAllRecords(){
    lock_guard<mutex> lock(mtx);
    vector<pair<string,string>> records;

    ifstream readStream(filePath);
    if(!readStream.is_open()){
        return records;
    }

    string line;
    while(getline(readStream, line)){
        stringstream ss(line);
        string key, value;

        if(getline(ss, key, '|') && getline(ss, value)){
            records.push_back({key, value});
        }
    }
    readStream.close();
    return records;
}

bool FileHandler::rewriteAllRecords(const vector<pair<string, string>>& records){
    lock_guard<mutex> lock(mtx);

    if(writeStream.is_open()){
        writeStream.close();
    }

    writeStream.open(filePath, ios::out | ios::trunc);
    if(!writeStream.is_open()){
        return false;
    }

    for(const auto& record : records){
        writeStream << record.first << "|" << record.second << "\n";
    }

    writeStream.flush();
    writeStream.close();

    writeStream.open(filePath, ios::out | ios::app);
    return true;
}