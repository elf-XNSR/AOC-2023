#include <fstream> 
#include <iostream> 
#include <string> 

int main()
{
	int iNum = 0;
	//	create input stream for file.
	std::ifstream inputFile("input.txt");

	std::string curLine{};
	while (std::getline(inputFile, curLine)) {
		const size_t size = curLine.size();
		for (const char& curChar : curLine) {
			if ((int)curChar < 58) {
				//	first number in line
				iNum += ((int)curChar - 48) * 10;
				break;
			}
		}
		for (int nIndex = size - 1; nIndex >= 0; nIndex--) {
			const int curChar = (int)curLine.at(nIndex);
			if (curChar < 58) {
				iNum += curChar - 48;
				break;
			}
		}
	}
	std::cout << iNum << std::endl;
}
