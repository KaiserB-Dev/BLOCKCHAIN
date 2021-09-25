//Isaac Mejía F.

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP
#include "block.hpp"
#include <fstream>


    struct Blockchain{
        std::vector<block> blockchain;

        Blockchain();
        block newGenesis();
        void addBlock(const std::string data);
        void save_blockchain(Blockchain blockchain);
        void recover_blockchain(const std::string file);
    };

    std::ostream& operator<<(std::ostream& os, Blockchain b);

#endif
