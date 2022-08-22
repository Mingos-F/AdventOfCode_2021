#pragma once

class Day11 {
public:
	std::vector<std::vector<int>> octopuses;
	std::vector<std::vector<int>> octopusesCopy;
	int flashCount = 0;
	bool allFlash = false;

	struct position {
		int line;
		int column;

		position(int l, int c) {
			line = l;
			column = c;
		}

		friend bool operator==(const position a, const position b) {
			if (a.line == b.line && a.column == b.column) {
				return true;
			}
			else {
				return false;
			}
		}
	};

	void Solve();
private:

	void AllFlashed();
	void IncrementAll();
	void SeeIfFlashed();
	void Flash(const position p, std::vector<position>& alreadyFlashed);
	position Up(position p);
	position Down(position p);
	position Left(position p);
	position Right(position p);
};