#pragma once

class Day15 {
public:
	void Solve();

	int rowsSize = 0;
	std::vector<int> flatMatrix;
private:

	int minCostDijkstra(bool fiveTimes);

	int Up(int i) const;
	int Down(int i) const;
	int Left(int i) const;
	int Right(int i) const;

};