#include "../include/file_handler.hpp"

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