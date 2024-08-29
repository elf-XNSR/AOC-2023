#include "RelationPair.hpp"
#include <string>
#include <iostream>

uint32_t CRelationPair::extractInteger(std::string& string, int& position){
    std::string concatString = {};
    for (; position < string.length(); position++){
        if (std::isdigit(string.at(position))){
            concatString += string.at(position);
        }
        else if (concatString.length() > 0){
            break;
        }
    }
    return std::stoul(concatString);
}

void CRelationPair::fillRelationPair(std::string& string){
    int position = 0;
    const uint32_t relationTwoStart = extractInteger(string, position);
    const uint32_t relationOneStart = extractInteger(string, position);
    const uint32_t relationRange = extractInteger(string, position);

    this->vecRelationPairIn.push_back(
        {relationOneStart,
         relationOneStart + relationRange}
    );

    this->vecRelationPairOut.push_back(
        {relationTwoStart,
         relationTwoStart + relationRange}
    );
}

uint32_t CRelationPair::remapRelatedValue(const uint32_t value) const{
    const int index = this->getIndexInVec(value);
    if (index == -1){
        return value;
    }
    const uint32_t offset = value - this->vecRelationPairIn.at(index).first;
    const uint32_t newBase = this->vecRelationPairOut.at(index).first;
    return newBase + offset;
}

int CRelationPair::getIndexInVec(const uint32_t value) const{
    for (int index = 0; index < this->vecRelationPairIn.size(); index++){
        const std::pair<uint32_t, uint32_t>& pair = this->vecRelationPairIn.at(index);
        if (value > pair.first &&
            value < pair.second){
                return index;
        }
    }
    return -1;  //  unmapped
}
