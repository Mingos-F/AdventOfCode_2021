#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include "Day3.h"

int ConvertToDecimal(long long number);
std::vector<std::string> find(std::vector<std::string> input, int flag);

void Day3::Solve() {

    // What is the power consumption of the submarine ?
    // What is the life support rating of the submarine?

    std::ifstream inputFile("Day3.input");
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

    int numColums = input[0].size();
    std::vector<Count> zeroOneCount(numColums);

    for (auto&& element : input)
    {
        for (size_t i = 0; i < element.size(); i++)
        {
            if (element.at(i) == '1')
            {
                zeroOneCount[i].one++;
            }
            else
            {
                zeroOneCount[i].zero++;
            }
        }
    }

    std::string gammaRate = "";
    std::string epsilonRate = "";

    for (auto&& element : zeroOneCount)
    {
        if (element.one > element.zero)
        {
            gammaRate += '1';
            epsilonRate += '0';
        }
        else
        {
            gammaRate += '0';
            epsilonRate += '1';
        }
    }

    int gammaRateDecimal = ConvertToDecimal(std::stoll(gammaRate));
    int epsilonRateDecimal = ConvertToDecimal(std::stoll(epsilonRate));

    int output = gammaRateDecimal * epsilonRateDecimal;

    std::cout << "The power consumption is: " << output << std::endl;

    std::vector<std::string> oxygen = find(input, 0);
    std::vector<std::string> carbonDioxide = find(input, 1);

    int oxygenDecimal = ConvertToDecimal(std::stoll(oxygen[0]));
    int carbonDioxideDecimal = ConvertToDecimal(std::stoll(carbonDioxide[0]));

    output = oxygenDecimal * carbonDioxideDecimal;

    std::cout << "The life support rating of the submarine is: " << output << std::endl;
}

int ConvertToDecimal(long long number)
{
    int dec = 0, i = 0, rem;

    while (number != 0)
    {
        rem = number % 10;
        number /= 10;
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

// flag values are 0 and any other integer, 0 for oxygen and other integer for co2
std::vector<std::string> find(std::vector<std::string> input, int flag)
{
    int i = 0;
    int zero = 0;
    int one = 0;

    std::vector<std::string> keepVector;

    while (input.size() > 1)
    {
        for (auto&& element : input)
        {
            if (element.at(i) == '1')
            {
                one++;
            }
            else
            {
                zero++;
            }
        }

        for (auto&& element : input)
        {
            if (flag == 0)
            {
                if (one == zero)
                {
                    if (element.at(i) == '1')
                    {
                        keepVector.push_back(element);
                    }
                }
                else if (one > zero)
                {
                    if (element.at(i) == '1')
                    {
                        keepVector.push_back(element);
                    }
                }
                else
                {
                    if (element.at(i) == '0')
                    {
                        keepVector.push_back(element);
                    }
                }
            }
            else
            {
                if (one == zero)
                {
                    if (element.at(i) == '0')
                    {
                        keepVector.push_back(element);
                    }
                }
                else if (one > zero)
                {
                    if (element.at(i) == '0')
                    {
                        keepVector.push_back(element);
                    }
                }
                else
                {
                    if (element.at(i) == '1')
                    {
                        keepVector.push_back(element);
                    }
                }
            }
        }

        input = keepVector;
        keepVector = {};
        zero = 0;
        one = 0;
        i++;
    }

    return input;
}