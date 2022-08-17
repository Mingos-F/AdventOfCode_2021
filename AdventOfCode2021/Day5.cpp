#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Day5.h"


void Day5::Solve() {
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
        if (!l.is_horizontal_or_vertical())
            continue;

        for (auto i = l.start.x; i <= l.end.x; i++)
        {
            for (auto j = l.start.y; j <= l.end.y; j++)
            {
                p = { i, j };
                vents.emplace(p, 0);
                ++vents[p];
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


