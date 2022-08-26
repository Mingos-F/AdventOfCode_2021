#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "Day15.h"

void Day15::Solve() {

	// What is the lowest total risk of any path from the top left to the bottom right?

	std::ifstream inputFile("Day15.input");
	std::string aux = "";

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{

			for (auto& digit : aux)
			{
				flatMatrix.push_back(digit - '0');
			}

			if (rowsSize == 0) {
				rowsSize = flatMatrix.size();
			}

		}
	}


	std::cout << minCostDijkstra(false) << std::endl;
	std::cout << minCostDijkstra(true) << std::endl;

}

int Day15::minCostDijkstra(bool fiveTimes) {

	if (fiveTimes) {
		for (size_t i = 0; i < 5; i++)
		{

		}
	}


	// Mark all nodes unvisited
	// Assign infinity distance to all nodes excpect first
	auto univisitedIndex = std::unordered_set<int>{};
	auto distance = std::vector<int>{};

	for (size_t i = 0; i < flatMatrix.size(); i++)
	{
		univisitedIndex.insert(i);
		distance.push_back(INT_MAX);
	}

	distance[0] = 0;

	// Distance must not grow/shrink while distance lookup table is alive due to raw pointers.
	auto distanceLookup = std::vector<const int*>{};
	distanceLookup.push_back(&distance[0]);

	while (univisitedIndex.size() > 0) {

		// Select current node
		const auto* currentNode = distanceLookup.back();
		auto currentNodeIndex = static_cast<int>(currentNode - &distance[0]);
		auto currentNodeDistance = *currentNode;

		// Mark the current node as visited

		distanceLookup.pop_back();
		univisitedIndex.erase(currentNodeIndex);

		// Calculate distance

		bool distanceUpdated = false;
		auto CalculateDistanceNeighbors = [&](int neighborIndex) {

			if (neighborIndex == -1 || univisitedIndex.find(neighborIndex) == univisitedIndex.end()) {
				return;
			}

			auto updatedDistance = distance[currentNodeIndex] + flatMatrix[neighborIndex];
			if (updatedDistance < distance[neighborIndex])
			{
				distance[neighborIndex] = updatedDistance;

				// If this is the first time we've discovered the node on the search, add it to the distance lookup table.
				auto FindResult = std::find(distanceLookup.begin(), distanceLookup.end(), &distance[neighborIndex]);
				if (FindResult == distanceLookup.end())
				{
					distanceLookup.push_back(&distance[neighborIndex]);
				}

				distanceUpdated = true;
			}

		};

		CalculateDistanceNeighbors(Up(currentNodeIndex));
		CalculateDistanceNeighbors(Down(currentNodeIndex));
		CalculateDistanceNeighbors(Left(currentNodeIndex));
		CalculateDistanceNeighbors(Right(currentNodeIndex));

		// Restore sort order on the distance lookup table. Final entry is smallest distance for next iteration.
		if (distanceUpdated)
		{
			std::sort(
				distanceLookup.begin(),
				distanceLookup.end(),
				[](const int*& Left, const int*& Right) { return *Left > *Right; });
		}
	}

	return distance[flatMatrix.size() - 1];
}

int Day15::Up(int i) const {
	if (i -  rowsSize >= 0) {
		return i - rowsSize;
	}
	else {
		return -1;
	}
}

int Day15::Down(int i) const {
	if (i < flatMatrix.size() - 1) {
		return i + rowsSize;
	}
	else {
		return -1;
	}
}

int Day15::Left(int i) const {
	if (i % rowsSize >= 1) {
		return i - 1;
	}
	else {
		return -1;
	}
}

int Day15::Right(int i) const {
	if (i % rowsSize < rowsSize) {
		return i + 1;
	}
	else {
		return -1;
	}
}
