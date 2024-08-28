#include <string>   //  string, stoi
#include <ctype.h>  //  isdigit
#include <array>    //  array
#include <iostream> //  cout
#include <fstream>  //  inputstream

constexpr std::array<int, 3> maxColours {14, 13, 12};  //  {blue, green, red}

bool getColour(int& position, std::string& inString, std::string& outString){
    for (position; position < inString.length(); position++){
        char character = inString.at(position);

        //  Game x: or cube count restart should return false;
        if (character == ':' || character == ';'){
            return false;
        }
        else if (character == ' '){
            continue;
        }

        //  "14 blue" should return "14b"
        // if we have a number, append and continue
        if (std::isdigit(character)){
            outString.push_back(character);
            continue;
        }
        else if (outString.length() > 0){
            //  reached colour, append first letter of colour and return
            outString.push_back(character);
            return true;
        }
        continue;
    }
    return false;
}

int colourToArrayPos(char startingCharacter){
    switch ((int)startingCharacter){
        case (int)'b': return 0;
        case (int)'g': return 1;
        case (int)'r': return 2;
    }
    return 3;   //  weird
}

bool colourCheck(std::array<int, 3>& curColours){
    for (int n = 0; n < curColours.size(); n++){
        if(curColours[n] > maxColours[n]){
            return false;
        }
        continue;
    }
    return true;
}

bool checkLine(std::string& string){
    std::array<int, 3> curColours = {0,0,0};
    for (int n = 0; n < string.length(); n++){
        std::string colour{};
        if (getColour(n, string, colour)){
            const int colourNum = colourToArrayPos(colour.back());
            colour.pop_back();
            curColours[colourNum] += std::stoi(colour);
        }
        else if (!colourCheck(curColours)){
            return false;
        }
        else{
            curColours = {0,0,0};
            colour = "";
            continue;
        }
    }
    return true;
}

int getGameNumber(std::string& string){
    std::string tempString{};
    for (int n = 5; n < string.length(); n++){
        //  Starts at the first number.
        if (string.at(n) == ':'){
            return std::stoi(tempString);
        }

        tempString.push_back(string.at(n));
    }

    return std::stoi(tempString);
}

int main(){
    int sumOfValidGames = 0;
    std::ifstream inputFile("input.txt");
    std::string curLine{};
    //  Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    while(std::getline(inputFile, curLine)){
        //  Don't get the game index until required.
        if (checkLine(curLine)){
            sumOfValidGames += getGameNumber(curLine);
        }
        continue;
    }

    std::cout << sumOfValidGames << std::endl;

    return 1;
}
