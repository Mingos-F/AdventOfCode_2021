#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Day5.h"



void Day5::Solve() {

	FindPoints(false);
	FindPoints(true);
}

void Day5::FindPoints(bool flag) {

	std::ifstream inputFile("Day5.input");

	if (!inputFile.is_open())
	{
		std::cerr << "Error opening file." << std::endl;
	}

	std::unordered_map<Point, int, PointHasher> vents;

	Line l;
	Point p;


	while (inputFile >> l)
	{
		if (l.is_vertical()) {

			for (auto i = l.start.x; i <= l.end.x; i++)
			{
				p = { i,l.start.y };
				vents.try_emplace(p, 0);
				++vents[p];
			}
		}
		else if (l.is_horizontal()) {
			for (auto i = l.start.y; i <= l.end.y; i++)
			{
				p = { l.start.x, i };
				vents.try_emplace(p, 0);
				++vents[p];
			}
		}
		else if (flag) {

			if (l.start.y < l.end.y)
			{
				int currentX = l.start.x;
				int currentY = l.start.y;

				while (currentX <= l.end.x && currentY <= l.end.y)
				{
					p = { currentX, currentY };
					vents.try_emplace(p, 0);
					++vents[p];

					++currentX;
					++currentY;
				}
			}
			else if (l.start.y > l.end.y)
			{
				int currentX = l.start.x;
				int currentY = l.start.y;

				while (currentX <= l.end.x && currentY >= l.end.y)
				{
					p = { currentX, currentY };
					vents.try_emplace(p, 0);
					++vents[p];

					++currentX;
					--currentY;
				}
			}
		}
	}

	int output = 0;

	for (auto&& vent : vents)
	{
		
		int currentVent = vent.second;
		if (currentVent >= 2)
		{
			++output;
		}
	}

	std::cout << "Unique intersections: " << output << "\n";
}