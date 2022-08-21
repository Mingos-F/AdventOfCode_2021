#pragma once
#include <unordered_map>

class Day10 {
public:
	void Solve();
private:
	std::unordered_map<char, int> points = {
		{ ')', 3},
		{ ']', 57},
		{ '}', 1197},
		{ '>', 25137}
	};

	std::unordered_map<char, char> chunkChars = {
		{')', '('},
		{']', '['},
		{'}', '{'},
		{'>', '<'}
	};

};