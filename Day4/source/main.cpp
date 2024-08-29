#include <cctype>
#include <fstream>  //  input stream
#include <string>   //  string, stoi
#include <utility>  //  pair
#include <iostream> //  cout

//  Iterates through string until entire number has been discovered, returns it.
int getIntFromString(std::string& string, int& position){
    std::string concatString = {};
    for (; position < string.length(); position++){
        if (std::isdigit(string.at(position))){
            concatString += string.at(position);
            continue;
        }
        else if (concatString.length() > 0){
            break;
        }
        continue;
    }
    return std::stoi(concatString);
}

void parseEntryToPair(std::string& string, std::pair<std::pair<int, int>, std::pair<int, int>>& elfPairing){
    int position = 0;
    elfPairing.first.first = getIntFromString(string, position);
    elfPairing.first.second = getIntFromString(string, position);
    elfPairing.second.first = getIntFromString(string, position);
    elfPairing.second.second = getIntFromString(string, position);
}

//  Checks if either pair eclipses the other.
bool checkPair(std::pair<std::pair<int, int>, std::pair<int, int>>& elfPairing){
    if ((elfPairing.first.first <= elfPairing.second.first &&
        elfPairing.first.second >= elfPairing.second.second) ||
        (elfPairing.second.first <= elfPairing.first.first &&
        elfPairing.second.second >= elfPairing.first.second)){
            return false;
    }
    return true;
}

int main(){
    int sumOfElves = 0;

    std::ifstream inputFile("input.txt");
    std::string curLine{};

    while(std::getline(inputFile, curLine)){
        std::pair<std::pair<int, int>, std::pair<int, int>> elfPairing = {};
        //  12-38,12-37
        parseEntryToPair(curLine, elfPairing);
        if (!checkPair(elfPairing)){
            sumOfElves++;
        }
    }

    std::cout << sumOfElves << std::endl;

    return 1;
}
