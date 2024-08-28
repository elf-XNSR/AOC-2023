#include <string>   //  string
#include <fstream>  //  input stream
#include <array>
#include <utility>  //  pair
#include <iostream>
#include <ctype.h>


//  Writes lines to parsingRows[index][1]
void addSchemaLine(std::string& string, std::array<std::pair<char, char>, 140>& parsingRows){
    //  iter through each character & write to parsingRows
    for (int index = 0; index < string.length(); index++){
        parsingRows[index].second = string.at(index);
    }
}

//  Writes parsingRows.second to parsingRows.first
void cycleRows(std::array<std::pair<char, char>, 140>& parsingRows){
    for (std::pair<char, char>& curPair : parsingRows){
        curPair.first = curPair.second;
    }
}

//  Casts a char to int and checks value to determine if it's a digit
//bool isDigit(char character){
//    return (int)character > 47 && (int)character < 58;
//}

//  Checks if a char is a symbol or not
bool isSymbol(char character){
    return !(std::isdigit(character) || character == '.' || !character);
}

//  Used for preventing duplicates
void clear(char& character){
    character = '.';
}

//  Discovers full number from provided digit that makes up number, this number is valid
int findFullNumber(std::array<std::pair<char, char>, 140>& parsingRows, const int position, const bool first){
    std::string tempString = "";
    tempString = tempString + (first ? parsingRows[position].first : parsingRows[position].second);
    clear(first ? parsingRows[position].first : parsingRows[position].second);
    //  Discover to the left first.
    for (int curIndex = position - 1; curIndex > 0; curIndex--){
        char character = first ? parsingRows[curIndex].first : parsingRows[curIndex].second;
        if (std::isdigit(character)){
            clear(first ? parsingRows[curIndex].first : parsingRows[curIndex].second);
            tempString = character + tempString;
            continue;
        }
        break;
    }
    //  Discover to the right;
    for (int curIndex = position + 1; curIndex < 140; curIndex++){
        char character = first ? parsingRows[curIndex].first : parsingRows[curIndex].second;
        if (std::isdigit(character)){
            clear(first ? parsingRows[curIndex].first : parsingRows[curIndex].second);
            tempString = tempString + character;
            continue;
        }
        break;
    }

    //std::cout << "Num:  " << std::stoi(tempString) << "\ntempString:  " << tempString << "\nposition:  " << position << "\n";
    return std::stoi(tempString);
}

//  Checks each pair to find a symbol, followed by finding and returning nearby part numbers
int findNearSymbol(std::array<std::pair<char, char>, 140>& parsingRows, const int position){
    int retVal = 0;
    //  No valid symbols in this pair, return 0
    if (!isSymbol(parsingRows[position].first) && !isSymbol(parsingRows[position].second)){
        return 0;
    }

    for (int posOffset = -1; posOffset < 2; posOffset++){
        if (std::isdigit(parsingRows[position + posOffset].first)){
            retVal += findFullNumber(parsingRows, position + posOffset, true);
        }
        if (std::isdigit(parsingRows[position + posOffset].second)){
            retVal += findFullNumber(parsingRows, position + posOffset, false);
        }
    }

    return retVal;
}

//  Goes through all characters in parsingRows and checks for possible part numbers
int partsFromLine(std::array<std::pair<char, char>, 140>& parsingRows){
    //  Keep a running tally of our part numbers, return when we are done with parsingRows
    int retVal = 0;
    for (int arrayIndex = 0; arrayIndex < parsingRows.size(); arrayIndex++){
        retVal += findNearSymbol(parsingRows, arrayIndex);
    }

    return retVal;
}

int main(){
    int sumOfParts = 0;

    std::array<std::pair<char, char>, 140> parsingRows = {};

    std::ifstream inputFile("input.txt");
    std::string curLine{};
    while(std::getline(inputFile, curLine)){
        addSchemaLine(curLine, parsingRows);

        sumOfParts += partsFromLine(parsingRows);

        cycleRows(parsingRows);
    }

    std::cout << sumOfParts << std::endl;

    return 1;
}
