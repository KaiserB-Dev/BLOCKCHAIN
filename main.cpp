#include<iostream>
//Isaac Mejía F.

#include "block.hpp"
#include"blockchain.hpp"


int main(){

    
    Blockchain bc;

    bc.addBlock("A->B 5BTC");
    bc.addBlock("C->Z 100BTC");

    std::cout<<bc<<"\n";


    return 0;
}