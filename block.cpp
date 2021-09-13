//Isaac Mejía F.

#include "block.hpp"
#include <windows.h>

block::block(const std::string data, std::string prevHash){
    auto time = std::chrono::system_clock::now();
    int timestamp = std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count();
    this->data = data;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    

    this->hash = mineValidHash(this->data, this->prevHash, this->timestamp);
}

std::string block::getHash(){
    return this->hash;
}


std::ostream& operator<<(std::ostream& os, block b){
    os<< "[ data: "<<b.data<<std::endl;
    os<< " prevhash: "<<b.prevHash<<std::endl;
    os<< " hash: "<<b.hash<<" ]";

    return os;
}

bool isValidHash(std::string hash){
    bool isValid = false;
    if(hash.find("00") == 0){
        isValid=true;
        
    }
    return isValid;
}

std::string mineValidHash(const std::string data, std::string prevHash, int timestamp){
    int magicValue = 0;
    std::string headers = "";
    std::string hash;
    headers += data;
    headers += prevHash;
    headers += timestamp;

    while(true){
        headers.push_back(magicValue);
        hash = sha256(headers);
        if(isValidHash(hash)){
            break;
        }
        else{
            headers.pop_back();
            ++magicValue;
        }
        std::cout<<"INCOGNITA: "<<magicValue<<"\n";
        std::cout<<"HASH:"<<hash<<"\n";
        system("cls");
    }
    return hash;
}