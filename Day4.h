#pragma once
#include <vector>

class Day4 {
public:
    void Solve();
private:
    struct BingoNumber
    {
        int number;
        bool marked = false;
    };

    struct BingoBoard
    {
        std::vector<std::vector<BingoNumber>> lines;
        bool won = false;
    };
};