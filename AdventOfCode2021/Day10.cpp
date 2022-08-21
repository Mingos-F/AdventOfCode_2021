#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Day10.h"


void Day10::Solve() {

	// What is the total syntax error score for those errors?
	// What is the middle score?

	std::ifstream inputFile("Day10.input");
	std::string aux = "";
	std::vector<std::string> line;
	std::vector<std::string> incompleteLines;
	std::vector<char> incorrectClosingChar;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			line.push_back(aux);
		}
	}

	for (auto&& element : line) {

		int incorrect = false;

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
					incorrect = true;
					break;
				}
			}
		}

		if (!incorrect) {
			incompleteLines.push_back(element);
		}
	}

	int output = 0;

	for (auto&& element : pointsError) {
		int nTimes = std::count(incorrectClosingChar.begin(), incorrectClosingChar.end(), element.first);
		output += nTimes * element.second;
	}

	std::cout << "The total syntax error score is: " << output << std::endl;


	std::vector<std::string> closingCharacters;

	for (auto&& element : incompleteLines) {

		std::string constructClosingCharacters = "";

		for (int i = element.size() - 1; i > -1; i--)
		{
			switch (element[i])
			{
			case '(':
				constructClosingCharacters += ')';
				break;
			case '[':
				constructClosingCharacters += ']';
				break;
			case '{':
				constructClosingCharacters += '}';
				break;
			case '<':
				constructClosingCharacters += '>';
				break;
			default:
				break;
			}
		}

		closingCharacters.push_back(constructClosingCharacters);
	}

	std::vector<int64_t> finalPoints;

	for (auto&& line : closingCharacters) {
		int64_t pointsLine = 0;
		for (int i = 0; i < line.size(); i++)
		{
			switch (line[i])
			{
			case ')':
				pointsLine *= 5;
				pointsLine += pointsAdding.find(')')->second;
				break;
			case ']':
				pointsLine *= 5;
				pointsLine += pointsAdding.find(']')->second;
				break;
			case '}':
				pointsLine *= 5;
				pointsLine += pointsAdding.find('}')->second;
				break;
			case '>':
				pointsLine *= 5;
				pointsLine += pointsAdding.find('>')->second;
				break;
			default:
				break;
			}
		}
		finalPoints.push_back(pointsLine);
	}

	std::sort(finalPoints.begin(), finalPoints.end(), std::less<int64_t>{});

	int midleScore = (ceil((float)finalPoints.size() / 2.0)-1);

	std::cout << "The middle score is :" << finalPoints[midleScore] << std::endl;
}