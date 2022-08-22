#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Day11.h"

void Day11::Solve() {

	// How many total flashes are there after 100 steps?
	// What is the first step during which all octopuses flash?

	std::ifstream inputFile("Day11.input");
	std::string aux = "";

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			std::vector<int> octopusesLine = {};
			for (auto&& element : aux) {
				octopusesLine.push_back(element - '0');
			}

			octopuses.push_back(octopusesLine);
		}
	}



	for (size_t step = 0; step < 100; step++)
	{
		IncrementAll();
		SeeIfFlashed();
		AllFlashed();
	}

	std::cout << "Total flashes are there after 100 steps: " << flashCount << std::endl;
	
	int count = 100;

	while (!allFlash) {
		IncrementAll();
		SeeIfFlashed();
		AllFlashed();
		count++;
	}

	std::cout << "first step during which all octopuses flash: " << count << std::endl;
}

void Day11::IncrementAll() {
	for (int i = 0; i < octopuses.size(); i++)
	{
		for (int j = 0; j < octopuses[i].size(); j++)
		{
			octopuses[i][j]++;
		}
	}
}

void Day11::SeeIfFlashed() {
	std::vector<position> alreadyFlashed = {};

	for (int i = 0; i < octopuses.size(); i++)
	{
		for (int j = 0; j < octopuses[i].size(); j++)
		{
			if (octopuses[i][j] > 9) {
				Flash(position{ i,j }, alreadyFlashed);
			}
		}
	}
}
void Day11::AllFlashed() {

	int aux = 0;

	for (auto&& element : octopuses)
	{
		if (std::count(element.begin(), element.end(), 0) == element.size()) {
			aux++;
		}
	}

	if (aux == octopuses.size()) {
		allFlash = true;
	}
}

void Day11::Flash(const position p, std::vector<position>& alreadyFlashed) {

	if (p.line == -1 || p.column == -1 || (std::find(alreadyFlashed.begin(), alreadyFlashed.end(), p) != alreadyFlashed.end())) {
		return;
	}

	if (octopuses[p.line][p.column] < 9) {
		octopuses[p.line][p.column]++;
		return;
	}

	alreadyFlashed.push_back(p);
	flashCount++;
	octopuses[p.line][p.column] = 0;


	Flash(Up(p), alreadyFlashed);
	Flash(Down(p), alreadyFlashed);
	Flash(Left(p), alreadyFlashed);
	Flash(Right(p), alreadyFlashed);
	Flash(Up(Left(p)), alreadyFlashed);
	Flash(Up(Right(p)), alreadyFlashed);
	Flash(Down(Left(p)), alreadyFlashed);
	Flash(Down(Right(p)), alreadyFlashed);
}

Day11::position Day11::Up(position p) {

	if (p.line != 0) {
		p.line--;
		return p;
	}

	return Day11::position{ -1,-1 };
}

Day11::position Day11::Down(position p) {

	if (p.line != Day11::octopuses.size() - 1) {
		p.line++;
		return p;
	}

	return Day11::position{ -1,-1 };
}

Day11::position Day11::Left(position p) {

	if (p.column != 0) {
		p.column--;
		return p;
	}

	return Day11::position{ -1,-1 };
}

Day11::position Day11::Right(position p) {

	if (p.column != Day11::octopuses.at(0).size() - 1) {
		p.column++;
		return p;
	}

	return Day11::position{ -1,-1 };
}