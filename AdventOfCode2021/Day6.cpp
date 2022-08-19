#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Day6.h"
#include "Functions.h"


void Day6::Solve() {

	// How many lanternfish would there be after 80 days?

	Functions f;

	std::ifstream inputFile("Day6.input");
	std::string aux = "";
	std::vector<std::string> splitResultString;
	std::vector<int> lanterFish;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			splitResultString = f.SplitStr(aux, ",");

			for (auto&& element : splitResultString)
			{
				lanterFish.push_back(stoi(element));
			}
		}
	}

	int fishToAdd = 0;

	for (size_t i = 0; i < 80; i++)
	{
		for (auto&& element :lanterFish)
		{
			if (element > 0) {
				element--;
			}
			else if (element == 0) {
				element = 6;
				fishToAdd++;
			}
		}

		for (size_t i = 0; i < fishToAdd; i++)
		{
			lanterFish.push_back(8);
		}
		fishToAdd = 0;
	}

	std::cout << "After 80 days there are: " << lanterFish.size() << " lanternfish" << std::endl;
}	