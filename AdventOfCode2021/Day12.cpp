#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Day12.h"
#include "Functions.h"

void Day12::Solve() {

	CalculatePaths(false);
	CalculatePaths(true);

}

void Day12::CalculatePaths(bool revisit) {

	// How many paths through this cave system are there that visit small caves at most once?

	std::unordered_map<std::string, std::unordered_set<std::string>> Graph;

	Functions f;

	std::ifstream inputFile("Day12.input");
	std::string aux = "";
	std::vector<std::string> splitStringResult;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			splitStringResult = f.SplitStr(aux, "-");

			Graph.try_emplace(splitStringResult[0], std::unordered_set<std::string>());
			Graph.try_emplace(splitStringResult[1], std::unordered_set<std::string>());
			Graph[splitStringResult[0]].insert(splitStringResult[1]);
			Graph[splitStringResult[1]].insert(splitStringResult[0]);
		}
	}



	std::vector<std::vector<std::string>> finishedPaths;

	// variable that stores all incomplete paths found
	std::vector<std::vector<std::string>> foundPaths;
	// start the path at start node
	foundPaths.push_back(std::vector<std::string>{"start"});

	bool foundAllPaths = false;

	// loop until all paths have been found
	while (!foundAllPaths) {

		foundAllPaths = true;

		// variable to store paths found in current iteration
		std::vector<std::vector<std::string>> currentPaths;

		// iterate trough all of the incomplete found paths
		for (auto&& path : foundPaths) {

			// get the node we are currently situated
			auto currentNode = path[path.size() - 1];

			// get the connections of that node
			auto connectedNodes = Graph.at(currentNode);

			// iterate trough all the connected nodes
			for (auto&& node : connectedNodes) {

				// ignore connections to start
				if (node == "start") {
					continue;
				}

				// end the path
				if (node == "end") {
					auto finishedPath = path;
					finishedPath.push_back(node);
					finishedPaths.push_back(finishedPath);
					continue;
				}

				// check if connection is lower case
				if (node[0] >= 'a' && node[0] <= 'z') {

					// check if this node was already visited
					if (std::find(path.begin(), path.end(), node) != path.end()) {
						if (!revisit) {
							continue;
						}

						bool visitedSmall = false;
						for (int i = 1; i < path.size(); i++)
						{
							auto previousPath = path[i];

							if (previousPath[0] >= 'a' && previousPath[0] <= 'z') {

								visitedSmall = std::find(path.begin() + i + 1, path.end(), previousPath) != path.end();
								if (visitedSmall) {
									break;
								}
							}
						}

						if (visitedSmall) {
							continue;
						}
					}
				}

				// this means it either is a upercase node or the first time connection to a lower case node
				auto currentPath = path;
				currentPath.push_back(node);
				currentPaths.push_back(currentPath);
				foundAllPaths = false;
			}
		}

		foundPaths.swap(currentPaths);
	}

	std::cout << finishedPaths.size() << std::endl;
}