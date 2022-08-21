#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Day10.h"


void Day10::Solve() {

	// What is the total syntax error score for those errors?

	std::ifstream inputFile("Day10.input");
	std::string aux = "";
	std::vector<std::string> line;
	std::vector<char> incorrectClosingChar;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			line.push_back(aux);
		}
	}

	for (auto&& element : line) {

		for (size_t i = 0; i < element.size(); i++)
		{
			std::unordered_map<char, char>::const_iterator got = chunkChars.find(element[i]);

			if (got != chunkChars.end()) {

				if (element[i - 1] == got->second) {
					element.erase(i - 1,2);
					i = 0;
				}
				else {
					incorrectClosingChar.push_back(element[i]);
					break;
				}
			}
		}
	}

	int output = 0;

	for (auto&& element : points) {
		int nTimes = std::count(incorrectClosingChar.begin(), incorrectClosingChar.end(), element.first);
		output += nTimes * element.second;
	}

	std::cout << "The total syntax error score is: " << output << std::endl;
}