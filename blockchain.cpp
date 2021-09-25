//Isaac Mejía F.

#include"blockchain.hpp"

Blockchain::Blockchain(){
    std::ifstream data("blockchain.txt");
    std::string datax2;

    //data. ?  blockchain.push_back(this->newGenesis()) : recover_blockchain("blockchain.txt");
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
        os<<"BLOQUE NUMERO: "<<i<<std::endl;
        os<<b.blockchain[i]<<",\n\n";
    }

    os<<"} \n";

    return os;
}

void Blockchain::save_blockchain(Blockchain blockchain){
    std::ofstream l("Blockchain.txt");
    l<<blockchain;
}

void Blockchain::recover_blockchain(const std::string file){
    std::ifstream blockchain_file(file);

    std::string temp_storage;

    while(!blockchain_file.eof()){
        blockchain_file>>temp_storage;
    }

    std::cout<<temp_storage<<std::endl;

    blockchain_file.close();

}
