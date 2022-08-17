#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Day4.h"

std::vector<std::string> SplitStr(std::string str, std::string deli);

void Day4::Solve() {

    // What will your final score be if you choose that board ?
    // Figure out which board will win last. Once it wins, what would its final score be?

    std::ifstream inputFile("Day4.input");
    std::string aux = "";
    std::vector<int> inputOrder;
    std::vector<std::string> splitResultString;

    std::vector<BingoBoard> bingoBoards;
    BingoBoard bBoard;
    std::vector<BingoNumber> line;
    BingoNumber bn;

    if (inputFile.is_open())
    {

        std::getline(inputFile, aux);

        splitResultString = SplitStr(aux, ",");

        std::transform(splitResultString.begin(), splitResultString.end(), std::back_inserter(inputOrder),
            [&](std::string s)
            {
                return stoi(s);
            });

        while (std::getline(inputFile, aux))
        {
            if (aux != "")
            {
                splitResultString = SplitStr(aux, " ");

                for (auto&& element : splitResultString)
                {
                    if (element != "")
                    {
                        bn.number = stoi(element);
                        line.push_back(bn);
                    }
                }
                bBoard.lines.push_back(line);
                line = {};
            }

            if (bBoard.lines.size() == 5)
            {
                bingoBoards.push_back(bBoard);
                bBoard = {};
            }
        }
    }

    inputFile.close();

    int i = 0;
    int firstWinNumber = 0;
    int lastWinNumber = 0;
    int wonLine = 0;
    bool firstwonfound = false;
    std::vector<int> wonColum = { 0, 0, 0, 0, 0 };
    BingoBoard firstWinBingoBoard;
    BingoBoard lastWinBingoBoard;

    for (auto&& element : inputOrder)
    {

        for (auto&& board : bingoBoards)
        {
            if (!board.won)
            {
                for (auto&& line : board.lines)
                {
                    for (auto&& n : line)
                    {
                        if (n.number == element && !n.marked)
                        {
                            n.marked = true;
                        }

                        if (n.marked)
                        {
                            switch (i)
                            {
                            case 0:
                                wonColum[i]++;
                                break;
                            case 1:
                                wonColum[i]++;
                                break;
                            case 2:
                                wonColum[i]++;
                                break;
                            case 3:
                                wonColum[i]++;
                                break;
                            case 4:
                                wonColum[i]++;
                                break;
                            }
                            wonLine++;
                        }
                        i++;
                    }

                    if (wonLine == 5 && !firstwonfound)
                    {
                        board.won = true;
                        firstwonfound = true;
                        firstWinBingoBoard = board;
                        firstWinNumber = element;
                    }
                    else if (wonLine == 5 && firstwonfound)
                    {
                        board.won = true;
                        lastWinBingoBoard = board;
                        lastWinNumber = element;
                    }

                    wonLine = 0;
                    i = 0;
                }

                for (auto&& colum : wonColum)
                {
                    if (colum == 5 && !firstwonfound)
                    {
                        board.won = true;
                        firstwonfound = true;
                        firstWinBingoBoard = board;
                        firstWinNumber = element;
                    }
                    else if (colum == 5 && firstwonfound)
                    {
                        board.won = true;
                        lastWinBingoBoard = board;
                        lastWinNumber = element;
                    }
                    else {
                        colum = 0;
                    }
                }
            }
        }
    }

    int sum = 0;
    int pointsFirstWinBingoBoard = 0;
    int pointsLastWinBingoBoard = 0;

    for (auto&& line : firstWinBingoBoard.lines)
    {
        for (auto&& n : line)
        {
            if (!n.marked)
            {
                sum += n.number;
            }
        }
    }

    pointsFirstWinBingoBoard = sum * firstWinNumber;
    sum = 0;

    for (auto&& line : lastWinBingoBoard.lines)
    {
        for (auto&& n : line)
        {
            if (!n.marked)
            {
                sum += n.number;
            }
        }
    }

    pointsLastWinBingoBoard = sum * lastWinNumber;

    std::cout << "The final score if the first winning board is chosen is: " << pointsFirstWinBingoBoard << std::endl;
    std::cout << "The final score if the last winning board is chosen is: " << pointsLastWinBingoBoard << std::endl;
}

std::vector<std::string> SplitStr(std::string str, std::string deli = " ")
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