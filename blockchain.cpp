#include"blockchain.hpp"

Blockchain::Blockchain(){
    blockchain.push_back(this->newGenesis());
}

void Blockchain::addBlock(const std::string data){
    block blockprev = this->blockchain[blockchain.size()-1];
    block blockNext(data, blockprev.getHash());
    blockchain.push_back(blockNext);
}

block Blockchain::newGenesis(){
    return block("BLOQUE GENESIS", "");
}

std::ostream& operator<<(std::ostream& os, Blockchain b){
    os<<"{ \n";
    for(size_t i=0; i<b.blockchain.size();++i){
        os<<b.blockchain[i]<<",\n\n";
    }

    os<<"} \n";

    return os;
}