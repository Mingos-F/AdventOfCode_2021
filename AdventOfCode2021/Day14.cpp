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
	Calculate(40);
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

	auto pairCount = std::unordered_map<std::string, int64_t>{};

	for (size_t i = 0; i + 1 < polymer.size(); i++)
	{
		auto pair = polymer.substr(i, 2);
		if (pairInsertionRules.find(pair) != pairInsertionRules.end()) {
			pairCount.try_emplace(pair,0);
			++pairCount[pair];
		}
	}



	for (size_t step = 0; step < nSteps; step++)
	{
		auto nextPairCount = std::unordered_map<std::string, int64_t>{};

		for (auto& count : pairCount) {

			const auto currentPair = count.first;
			const auto currentCount = count.second;
			const auto insertChar = pairInsertionRules.at(currentPair);

			auto firstPair = std::string{ currentPair[0],insertChar };
			nextPairCount.try_emplace(firstPair, 0);
			nextPairCount[firstPair] += currentCount;

			auto secondPair = std::string{ insertChar, currentPair[1] };
			nextPairCount.try_emplace(secondPair, 0);
			nextPairCount[secondPair] += currentCount;
		}

		pairCount.swap(nextPairCount);
	}

	std::unordered_map<char, int64_t> charCount;
	charCount[polymer[0]] = 1;
	for (auto& count : pairCount)
	{
		const auto currentPair = count.first;
		const auto currentCount = count.second;
		charCount.try_emplace(currentPair[1], 0);
		charCount[currentPair[1]] += currentCount;
	}

	auto compare = [](const auto& left, const auto& right) { return left.second < right.second; };
	const auto& min = std::min_element(charCount.begin(), charCount.end(), compare);
	const auto& max = std::max_element(charCount.begin(), charCount.end(), compare);

	std::cout << "Most common element minus least common element is: " << max->second - min->second << std::endl;

}