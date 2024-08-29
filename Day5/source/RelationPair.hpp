#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include <string>

class CRelationPair{
public:
    void fillRelationPair(std::string& string);
    uint32_t remapRelatedValue(const uint32_t value) const;

    static uint32_t extractInteger(std::string& string, int& position);
    //void fillRelationPair(std::string& string);
private:
    int getIndexInVec(const uint32_t value) const;

    std::vector<std::pair<uint32_t, uint32_t>> vecRelationPairIn{};
    std::vector<std::pair<uint32_t, uint32_t>> vecRelationPairOut{};
};
