#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include "Day9.h"

void Day9::Solve() {

	// What is the sum of the risk levels of all low points on your heightmap?
	// What do you get if you multiply together the sizes of the three largest basins?

	std::ifstream inputFile("Day9.input");
	std::string aux = "";
	std::vector<std::vector<int>> heigthMatrix;
	std::vector<int> line;

	std::vector<ValueLocationMatrix> lowPoints;

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

			ValueLocationMatrix upValue = Up(heigthMatrix, i, j);
			ValueLocationMatrix downValue = Down(heigthMatrix, i, j);
			ValueLocationMatrix leftValue = Left(heigthMatrix, i, j);
			ValueLocationMatrix rightValue = Right(heigthMatrix, i, j);

			if (upValue.value != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, upValue.value);
			}

			if (downValue.value != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, downValue.value);
			}

			if (leftValue.value != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, leftValue.value);
			}

			if (rightValue.value != -1) {
				smallestAdjacentValue = std::min(smallestAdjacentValue, rightValue.value);
			}

			if (heigthMatrix[i][j] < smallestAdjacentValue) {
				ValueLocationMatrix vlm(heigthMatrix[i][j],i,j);
				lowPoints.push_back(vlm);
			}
		}
	}

	std::vector<int> basinSize;

	for (auto&& element : lowPoints)
	{
		basinSize.push_back(CalculateBasinSize(element, heigthMatrix));
	}

	std::sort(basinSize.begin(), basinSize.end(), std::greater<int>{});

	int output = 0;

	for (auto&& element : lowPoints)
	{
		element.value += 1;
		output += element.value;
	}

	std::cout << "The sum of the risk is: " << output << std::endl;
	std::cout << "The 3 largest basins multiplied euqlas: " << (basinSize[0] * basinSize[1] * basinSize[2]) << std::endl;
}

Day9::ValueLocationMatrix Day9::Up(std::vector<std::vector<int>>& matrix, size_t line, size_t column) {

	ValueLocationMatrix output(-1,-1,-1);

	if (line > 0) {
		--line;
		output.value = matrix[line][column];
		output.line = line;
		output.column = column;
	}

	return output;
}

Day9::ValueLocationMatrix Day9::Down(std::vector<std::vector<int>>& matrix, size_t line, size_t column) {
	ValueLocationMatrix output(-1, -1, -1);

	if (line < (matrix.size() - 1)) {
		++line;
		output.value = matrix[line][column];
		output.line = line;
		output.column = column;
	}

	return output;
}

Day9::ValueLocationMatrix Day9::Left(std::vector<std::vector<int>>& matrix, size_t line, size_t column) {
	ValueLocationMatrix output(-1, -1, -1);

	if (column > 0) {
		--column;
		output.value = matrix[line][column];
		output.line = line;
		output.column = column;
	}

	return output;
}

Day9::ValueLocationMatrix Day9::Right(std::vector<std::vector<int>>& matrix, size_t line, size_t column) {
	ValueLocationMatrix output(-1, -1, -1);

	if (column < (matrix[line].size() - 1)) {
		++column;
		output.value = matrix[line][column];
		output.line = line;
		output.column = column;
	}

	return output;
}

int Day9::CalculateBasinSize(ValueLocationMatrix lowPoint, std::vector<std::vector<int>>& matrix) {

	std::vector<ValueLocationMatrix> elementsInBasin;
	CalculateBasinSize(lowPoint, matrix, elementsInBasin);
	return elementsInBasin.size();
}

void Day9::CalculateBasinSize(ValueLocationMatrix lowPoint, std::vector<std::vector<int>>& matrix, std::vector<ValueLocationMatrix>& elementsInBasin) {
	
	for (auto&& element : elementsInBasin) {
		if (element == lowPoint) {
			return;
		}
	}

	if (lowPoint.value == -1 || lowPoint.value == 9) {
		return;
	}

	elementsInBasin.push_back(lowPoint);
	CalculateBasinSize(Up(matrix,lowPoint.line, lowPoint.column), matrix, elementsInBasin);
	CalculateBasinSize(Down(matrix, lowPoint.line, lowPoint.column), matrix, elementsInBasin);
	CalculateBasinSize(Left(matrix, lowPoint.line, lowPoint.column), matrix, elementsInBasin);
	CalculateBasinSize(Right(matrix, lowPoint.line, lowPoint.column), matrix, elementsInBasin);
}