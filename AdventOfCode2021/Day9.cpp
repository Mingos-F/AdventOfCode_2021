#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include "Day9.h"
#include "Functions.h"

void Day9::Solve() {

	// What is the sum of the risk levels of all low points on your heightmap?

	Functions f;

	std::ifstream inputFile("Day9.input");
	std::string aux = "";
	std::vector<std::vector<int>> heigthMatrix;
	std::vector<int> line;

	std::vector<int> output;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			for (auto&& element : aux) {
				line.push_back(element - '0');
			}

			heigthMatrix.push_back(line);
			line = {};
		}
	}

	for (size_t i = 0; i < heigthMatrix.size(); i++)
	{
		for (size_t j = 0; j < heigthMatrix[i].size(); j++)
		{
			int smallestAdjacentValue = 9;

			int upValue = Up(heigthMatrix, i, j);
			int downValue = Down(heigthMatrix, i, j);
			int leftValue = Left(heigthMatrix, i, j);
			int rightValue = Right(heigthMatrix, i, j);

			if (upValue != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, upValue);
			}

			if (downValue != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, downValue);
			}

			if (leftValue != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, leftValue);
			}

			if (rightValue != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, rightValue);
			}

			if (heigthMatrix[i][j] < smallestAdjacentValue) {
				output.push_back(heigthMatrix[i][j]);
			}
		}
	}

	for (auto&& element : output)
	{
		element += 1;
	}

	std::cout << "The sum of the risk is: " << std::accumulate(output.begin(), output.end(), 0) << std::endl;
}

int Day9::Up(std::vector<std::vector<int>>& matrix, int line, int column) {

	int output = -1;

	if (line > 0) {
		output = matrix[--line][column];
	}

	return output;
}

int Day9::Down(std::vector<std::vector<int>>& matrix, int line, int column) {
	int output = -1;

	if (line < (matrix.size() - 1)) {
		output = matrix[++line][column];
	}

	return output;
}

int Day9::Left(std::vector<std::vector<int>>& matrix, int line, int column) {
	int output = -1;

	if (column > 0) {
		output = matrix[line][--column];
	}

	return output;
}

int Day9::Right(std::vector<std::vector<int>>& matrix, int line, int column) {
	int output = -1;

	if (column < (matrix[line].size() - 1)) {
		output = matrix[line][++column];
	}

	return output;
}