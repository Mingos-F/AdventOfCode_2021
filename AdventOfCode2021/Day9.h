#pragma once

class Day9 {
public:
	void Solve();
private:
	bool Test(const int tested, const int adjacent);
	int Up(std::vector<std::vector<int>>& matrix, int line, int column);
	int Down(std::vector<std::vector<int>>& matrix, int line, int column);
	int Left(std::vector<std::vector<int>>& matrix, int line, int column);
	int Right(std::vector<std::vector<int>>& matrix, int line, int column);
};