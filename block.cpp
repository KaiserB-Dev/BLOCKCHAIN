//Isaac Mejía F.

#include "block.hpp"
#include <windows.h>

block::block(const std::string data, std::string prevHash){
    auto time = std::chrono::system_clock::now();
    int timestamp = std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count();
    this->data = data;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    this -> ID_BLOCK = genIDBlock(this->data, this->prevHash, this->timestamp);
    

    this->ValidHash = mineValidHash(this->ID_BLOCK);
}

std::string block::getHash(){
    return this->ValidHash;
}


std::ostream& operator<<(std::ostream& os, block b){
    os<< "[data: "<<b.data<<std::endl;
    os<< " MAKER_ROOT: "<<b.ID_BLOCK<<std::endl;
    os<< " prevhash: "<<b.prevHash<<std::endl;
    os<< " hash: "<<b.ValidHash<<"]";

    return os;
}

bool isValidHash(std::string hash){
    bool isValid = false;
    if(hash.find("00") == 0){
        isValid=true;
        
    }
    return isValid;
}

std::string mineValidHash(std::string ID_BLOCK){
    int magicValue = 0;
    std::string hash;
    ID_BLOCK.pop_back();
    
    std::cout<<"INCOGNITA: ";
    cpos incog;
    std::cout<<"\nHASH: ";
    cpos jash;
    while(true){
        ID_BLOCK.push_back(magicValue);
        hash = sha256(ID_BLOCK);
        if(isValidHash(hash)){
            break;
        }
        else{
            ID_BLOCK.pop_back();
            ++magicValue;
        }
        incog.putxy();
        std::cout<<magicValue;
        jash.putxy();
        std::cout<<hash<<"\n";
    }
    std::cout<<std::endl;
    return hash;
}

std::string genIDBlock(const std::string data, std::string prevHash,  int timestamp){
    std::string ID_BLOCK;
    std::string headers = "";
    headers += data;
    headers += prevHash;
    headers += timestamp;

    ID_BLOCK = sha256(headers);

    return ID_BLOCK;
}
