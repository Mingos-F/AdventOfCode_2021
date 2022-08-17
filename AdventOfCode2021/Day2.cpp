#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include "Day2.h"

void Day2::Solve()
{
    // What do you get if you multiply your final horizontal position by your final depth?
    // What do you get if you multiply your final horizontal position by your final depth?


    Submarine initPosition;

    std::ifstream inputFile("Day2.input");
    std::string aux = "";
    std::vector<std::string> input;

    if (inputFile.is_open())
    {
        while (std::getline(inputFile, aux))
        {
            input.push_back(aux);
        }
    }

    inputFile.close();

    for (auto&& element : input)
    {
        switch (element.at(0))
        {
        case 'f':
            initPosition.horizontalPosition += (element.at(element.size() - 1) - '0');
            initPosition.depth2 += (element.at(element.size() - 1) - '0') * initPosition.aim;
            break;
        case 'd':
            initPosition.depth1 += (element.at(element.size() - 1) - '0');
            initPosition.aim += (element.at(element.size() - 1) - '0');
            break;
        case 'u':
            initPosition.depth1 -= (element.at(element.size() - 1) - '0');
            initPosition.aim -= (element.at(element.size() - 1) - '0');
            break;
        }
    }

    int output1 = initPosition.horizontalPosition * initPosition.depth1;
    int output2 = initPosition.horizontalPosition * initPosition.depth2;

    std::cout << "Horizotal position times depth is: " << output1 << std::endl;
    std::cout << "The final horizotal position times depth is: " << output2 << std::endl;

}

