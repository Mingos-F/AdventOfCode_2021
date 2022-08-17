#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Day1.h"

void Day1::Solve()
{
    // How many measurements are larger than the previous measurement?
    // How many sums are larger than the previous sum?



    std::ifstream inputFile("Day1.input");
    std::string aux = "";
    std::vector<int> input;

    if (inputFile.is_open())
    {
        while (std::getline(inputFile, aux))
        {
            input.push_back(stoi(aux));
        }
    }

    inputFile.close();

    int output1 = 0;
    int output2 = 0;
    int currentSum = 0;
    int previousSum = 0;
    int i = 0;

    for (auto iter = input.cbegin(); iter != input.cend(); iter++)
    {

        if (iter != input.cbegin())
        {
            if (*iter > *(iter - 1))
            {
                output1++;
            }
        }

        if (i >= 2)
        {
            currentSum = *iter + *(iter - 1) + *(iter - 2);

            if (currentSum > previousSum && previousSum != 0) {
                output2++;
            }

            previousSum = currentSum;
        }
        i++;
    }

    std::cout << "Number of mesurments larger than the previous is: " << output1 << std::endl;
    std::cout << "The number of larger than the previous is: " << output2 << std::endl;

};