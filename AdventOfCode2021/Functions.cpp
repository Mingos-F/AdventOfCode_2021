#include <cmath>
#include "Functions.h"

int Functions::ConvertToDecimal(long long number)
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


std::vector<std::string> Functions::SplitStr(std::string str, std::string deli = " ")
{
    int start = 0;
    int end = str.find(deli);

    std::vector<std::string> output;

    while (end != -1)
    {
        output.push_back(str.substr(start, end - start));
        start = end + deli.size();
        end = str.find(deli, start);
    }
    output.push_back(str.substr(start, end - start));
    return output;
}