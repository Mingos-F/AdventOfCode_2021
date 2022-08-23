#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "Day13.h"
#include "Functions.h"

void Day13::Solve() {
	CalculatePoints();
}

void Day13::CalculatePoints() {

	// How many dots are visible after completing just the first fold instruction on your transparent paper?
	// What code do you use to activate the infrared thermal imaging camera system?

	Functions f;

	std::ifstream inputFile("Day13.input");
	std::string aux = "";
	std::vector<std::string> splitStringResult1;
	std::vector<std::string> splitStringResult2;
	std::unordered_set<point, pointHasher> points;
	std::vector<fold> folds;

	int maxY = 0;
	int maxX = 0;

	bool onlyFirst = true;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			if (std::find(aux.begin(), aux.end(), ',') != aux.end()) {
				splitStringResult1 = f.SplitStr(aux, ",");

				int x, y;
				x = stoi(splitStringResult1[0]);
				y = stoi(splitStringResult1[1]);

				points.insert(point{ x,y });

				if (x > maxX)
					maxX = x;
				if (y > maxY)
					maxY = y;

			}
			else if (aux != "") {
				splitStringResult1 = f.SplitStr(aux, " ");
				splitStringResult2 = f.SplitStr(splitStringResult1[2], "=");
				folds.push_back(fold{ splitStringResult2[0], stoi(splitStringResult2[1]) });
			}

		}
	}

	int nColums = maxX;
	int nLines = maxY;


	for (auto& fold : folds)
	{
		std::unordered_set<point, pointHasher> newPoints;

		for (const auto& p : points)
		{
			if (fold.type == "y") {
				if (p.y > fold.location) {
					int distance = p.y - fold.location;
					newPoints.emplace(point{ p.x, fold.location - distance });
					continue;
				}

				newPoints.emplace(p);
			}
			else {
				if (p.x > fold.location) {
					int distance = p.x - fold.location;
					newPoints.emplace(point{ fold.location - distance, p.y });
					continue;
				}

				newPoints.emplace(p);
			}
		}


		points = newPoints;

		if (onlyFirst) {
			std::cout << "After completing just the first fold there are: " << points.size() << " dots visible" << std::endl << std::endl;
			onlyFirst = false;
		}

		if (fold.type == "y") {
			nLines = std::floor((double)nLines / 2);
		}
		else {
			nColums = std::floor((double)nColums / 2);
		}
	}

	std::vector<std::vector<std::string>> matrix(nLines, std::vector<std::string>(nColums,std::string(".")));

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			for (auto& p : points) {
				if (p.x == j && p.y == i) {
					matrix[i][j] = "#";
				}
			}
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}