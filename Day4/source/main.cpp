#include <cctype>
#include <fstream>  //  input stream
#include <string>   //  string, stoi
#include <vector>    //  vector
#include <iostream> //  cout
#include <cmath>    //  pow

//  Returns first occurence of number, or 0
int findCharacter(char character, std::string& string){
    for (int index = 0; index < string.length(); index++){
        if (string.at(index) == character){
            return index;
        }
    }
    return 0;
}

int extractNumber(std::string& string, int& position){
    std::string concatString = {};
    for (; position < string.length(); position++){
        if (std::isdigit(string.at(position))){
            concatString += string.at(position);
            continue;
        }
        else if (concatString.length() > 0){
            break;
        }
    }
    return std::stoi(concatString);
}

void fillWinningNumbers(std::vector<int>& winningNumbers, std::string& string){
    //  Look for '|' character
    int index = findCharacter('|', string);
    if (index == 0){
        return;
    }

    for (; index < string.length(); index++){
        winningNumbers.push_back(extractNumber(string, index));
    }
}

void fillObtainedNumbers(std::vector<int>& obtainedNumbers, std::string& string){
    const int maxIndex = findCharacter('|', string);
    int index = findCharacter(':', string);
    if (maxIndex == 0 || index == 0){
        return;
    }

    for (; index < maxIndex; index++){
        obtainedNumbers.push_back(extractNumber(string, index));
    }
}

int totalOverlaps(std::vector<int>& winningNumbers, std::vector<int>& obtainedNumbers){
    int amount = 0;
    for (int value : obtainedNumbers){
        //std::cout << "\n" << value << " | ";
        for (int compVal : winningNumbers){
            //std::cout << compVal << " | ";
            if (compVal == value){
                amount++;
                break;
            }
        }
    }
    return amount;
}

int tallyScore(std::vector<int>& winningNumbers, std::vector<int>& obtainedNumbers){
    const int scores = totalOverlaps(winningNumbers, obtainedNumbers);
    //std::cout <<  scores << "\n";
    if (scores <= 0){
        return 0;
    }
    return std::pow(2, (scores - 1));
}

int main(){
    int totalPoints = 0;

    std::ifstream inputFile("input.txt");
    std::string curLine{};

    while(std::getline(inputFile, curLine)){
        std::vector<int> winningNumbers={};
        std::vector<int> obtainedNumbers={};

        fillWinningNumbers(winningNumbers, curLine);
        fillObtainedNumbers(obtainedNumbers, curLine);

        totalPoints += tallyScore(winningNumbers, obtainedNumbers);
    }

    std::cout << totalPoints << std::endl;

    return 1;
}
