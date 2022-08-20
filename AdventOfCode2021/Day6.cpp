#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <numeric>
#include "Day6.h"
#include "Functions.h"


void Day6::Solve() {

	// How many lanternfish would there be after 80 days?
	// How many lanternfish would there be after 256 days?

	CalculateForDays(80);
	CalculateForDays(256);
}

void Day6::CalculateForDays(const int days) {
	Functions f;

	std::ifstream inputFile("Day6.input");
	std::string aux = "";
	std::vector<std::string> splitResultString;
	std::vector<int> initialFish;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			splitResultString = f.SplitStr(aux, ",");

			for (auto&& element : splitResultString)
			{
				initialFish.push_back(stoi(element));
			}
		}
	}

	constexpr int cycle = 9;

	std::array<int64_t, cycle> currentFish{};

	for (auto&& daysLeftCycle : initialFish)
	{
		++currentFish[daysLeftCycle];
	}

	for (size_t i = 0; i < days; i++)
	{
		std::array<int64_t, cycle> nextFish{};

		nextFish[6] = currentFish[0];
		nextFish[8] = currentFish[0];

		for (size_t i = 1; i < currentFish.size(); i++)
		{
			nextFish[i - 1] += currentFish[i];
		}

		currentFish = nextFish;
	}

	int64_t output = 0;

	for (size_t i = 0; i < currentFish.size(); i++)
	{
		output += currentFish[i];
	}

	std::cout << "After 80 days there are: " << output << " lanternfish" << std::endl;
}