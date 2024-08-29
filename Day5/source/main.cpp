#include <algorithm>
#include <cmath>    //  INFINITY
#include <iostream>
#include <fstream>
#include "RelationPair.hpp"

void keepLowest(const uint32_t value, uint32_t* retVal = nullptr){
    static uint32_t lowest = 0;
    if (retVal){
        *retVal = lowest;
        return;
    }

    lowest = lowest > 0 ? std::min(lowest, value) : value;
}

CRelationPair* createRelationPair(){
    return new CRelationPair();
}

uint32_t solveSeed(uint32_t value, std::vector<CRelationPair*>& solvePairs){
    for(CRelationPair* relationalPair : solvePairs){
        value = relationalPair->remapRelatedValue(value);
    }
    return value;
}

void extractSeeds(std::string& string, std::vector<uint32_t>& seeds){
    for (int index = 0; index < string.length(); index++){
        seeds.push_back(CRelationPair::extractInteger(string, index));
    }
}

int main(){
    std::vector<CRelationPair*> solvePairs{};
    std::vector<uint32_t> seeds{};

    std::ifstream inputFile("input.txt");
    std::string curLine{};

    //  get seeds
    std::getline(inputFile, curLine);
    extractSeeds(curLine, seeds);
    while(std::getline(inputFile, curLine)){
        if (curLine.empty()|| curLine.back() == ':'){
            continue;
        }

        solvePairs.push_back(createRelationPair());
        while(!curLine.empty()){
            solvePairs.back()->fillRelationPair(curLine);
            std::getline(inputFile, curLine);
        }
    }

    for (uint32_t value : seeds){
        keepLowest(solveSeed(value, solvePairs));
    }

    uint32_t final{};
    keepLowest(0, &final);
    std::cout << final << std::endl;

    return 1;
}
