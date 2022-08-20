#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Day7.h"
#include "Functions.h"

void Day7::Solve() {

	// How much fuel must they spend to align to that position ?

	IncreaseFuel(false);
	IncreaseFuel(true);
}

void Day7::IncreaseFuel(const bool flag) {

	Functions f;

	std::ifstream inputFile("Day7.input");
	std::string aux = "";
	std::vector<std::string> splitResultString;
	std::vector<int> horizontalPosition;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			splitResultString = f.SplitStr(aux, ",");

			for (auto&& element : splitResultString)
			{
				horizontalPosition.push_back(stoi(element));
			}
		}
	}

	auto minPosition = *std::min_element(horizontalPosition.begin(), horizontalPosition.end());
	auto maxPosition = *std::max_element(horizontalPosition.begin(), horizontalPosition.end());

	auto output = INT32_MAX;
	int minPositionFinal = 0;

	for (auto tryposition = minPosition; tryposition <= maxPosition; tryposition++) {
		auto curruntMin = 0;

		for (auto&& position : horizontalPosition) {
			auto n = abs(position - tryposition);

			if (flag) {
				curruntMin += (n * (n + 1)) / 2;
			}
			else {
				curruntMin += n;
			}
		}


		if (curruntMin < output) {
			output = curruntMin;
			minPositionFinal = tryposition;
		}
	}

	std::cout << "To align to " << minPositionFinal << " the fuel spent is: " << output << std::endl;
}