//Isaac Mejía F.

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP
#include "block.hpp"


    struct Blockchain{
        std::vector<block> blockchain;

        Blockchain();
        block newGenesis();
        void addBlock(const std::string data);
    };

    std::ostream& operator<<(std::ostream& os, Blockchain b);

#endif
