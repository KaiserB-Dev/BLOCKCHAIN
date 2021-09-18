//Isaac Mejía F.

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<string>
#include "sha256.hpp"
#include "ccontrol.hpp"
#include<ostream>
#include <vector>
#include<iostream>
#include<chrono>


class block{
    private:
        std::string data;
        std::string prevHash;
        std::string ValidHash;
        std::string ID_BLOCK;
        int timestamp;

    public:
        block(const std::string data, std::string prevHash);
        friend std::ostream& operator<<(std::ostream& os, block b);
        std::string getHash();
}; //Definicion de la clase bloque

std::string mineValidHash(std::string ID_BLOCK);
bool isValidHash(std::string hash);
std::string genIDBlock(const std::string data, std::string prevHash,  int timestamp);

#endif
