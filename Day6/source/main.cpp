#include <cctype>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int getStartIndex(std::string& string){
    for (int index = 0; index < string.length(); index++){
        if (string.at(index) == ':'){
            return index;
        }
    }
    return -1;  //  throw out of range
}

int extractInt(std::string& string, int& position){
    std::string concatString{};
    for (; position < string.length(); position++){
        if (std::isdigit(string.at(position))){
            concatString += string.at(position);
        }
        else if (concatString.length() > 0){
            break;
        }
    }
    return std::stoi(concatString);
}

int calcDistance(const int time, const int timeHeld){
    //  Remaining time * speed
    return (time-timeHeld)*timeHeld;
}

int calcWins(const int time, const int distance){
    int wins = 0;
    for (int timeHeld = 0; timeHeld < time; timeHeld++){
        if (calcDistance(time, timeHeld) > distance){
            wins++;
        }
    }
    return wins;
}

void fillVector(std::string& string, std::vector<int>& vector){
    int index = getStartIndex(string);
    for (; index < string.length(); index++){
        vector.push_back(extractInt(string, index));
    }
}

int solve(std::vector<int>& vecTimes, std::vector<int>& vecDistances){
    int solve = 1;
    for (int index = 0; index < vecTimes.size(); index++){
        solve *= calcWins(vecTimes[index], vecDistances[index]);
    }
    return solve;
}

int main(){
    std::ifstream inputFile("input.txt");
    std::string curLine{};

    std::vector<int> vecTimes{};
    std::vector<int> vecDistances{};

    std::getline(inputFile, curLine);
    fillVector(curLine, vecTimes);
    std::getline(inputFile, curLine);
    fillVector(curLine, vecDistances);

    std::cout << solve(vecTimes, vecDistances) << std::endl;

    return 1;
}
