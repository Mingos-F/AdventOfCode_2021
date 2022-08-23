#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include "Day14.h"
#include "Functions.h"

void Day14::Solve() {
	Calculate(10);
	//Calculate(40);
}

void Day14::Calculate(int nSteps) {

	// What do you get if you take the quantity of the most common element and subtract the quantity of the least common element?

	Functions f;

	std::ifstream inputFile("Day14.input");
	std::string aux = "";
	std::vector<std::string> splitStringResult1;

	std::string polymer;
	std::unordered_map<std::string, char> pairInsertionRules;


	if (inputFile.is_open())
	{
		std::getline(inputFile, polymer);
		std::getline(inputFile, aux);

		while (std::getline(inputFile, aux))
		{
			splitStringResult1 = f.SplitStr(aux, "->");
			splitStringResult1[0].erase(remove(splitStringResult1[0].begin(), splitStringResult1[0].end(), ' '), splitStringResult1[0].end());
			splitStringResult1[1].erase(remove(splitStringResult1[1].begin(), splitStringResult1[1].end(), ' '), splitStringResult1[1].end());
			pairInsertionRules.insert({ splitStringResult1[0], splitStringResult1[1].at(0) });
		}
	}


	for (size_t step = 0; step < nSteps; step++)
	{
		for (size_t i = 0; i < polymer.size() - 1; i++)
		{
			std::string pair = f.ReturnString(polymer[i]) + f.ReturnString(polymer[i + 1]);

			for (auto& rule : pairInsertionRules)
			{
				if (rule.first == pair) {
					polymer.insert(i + 1, f.ReturnString(rule.second));
					i++;
				}
			}
		}
	}

	int64_t max = 0;
	int64_t min = INT64_MAX;

	for (auto& letter : pairInsertionRules)
	{
		int64_t count = std::count(polymer.begin(), polymer.end(), letter.second);

		if (count > max) {
			max = count;
		}

		if (count < min) {
			min = count;
		}
	}

	std::cout << "Most common element minus least common element is: " << max - min << std::endl;

}