#pragma once

class Day9 {
public:
	void Solve();

	struct ValueLocationMatrix {
		int value;
		size_t line;
		size_t column;

		ValueLocationMatrix(int _value, size_t _line, size_t _column) {
			value = _value;
			line = _line;
			column = _column;
		}

		friend bool operator==(const ValueLocationMatrix& v1, const ValueLocationMatrix& v2) {
			if (v1.line == v2.line && v1.column == v2.column) {
				return true;
			}
			else {
				return false;
			}
		}
	};

private:
	
	ValueLocationMatrix Up(std::vector<std::vector<int>>& matrix, size_t line, size_t column);
	ValueLocationMatrix Down(std::vector<std::vector<int>>& matrix, size_t line, size_t column);
	ValueLocationMatrix Left(std::vector<std::vector<int>>& matrix, size_t line, size_t column);
	ValueLocationMatrix Right(std::vector<std::vector<int>>& matrix, size_t line, size_t column);
	int CalculateBasinSize(ValueLocationMatrix lowPoint, std::vector<std::vector<int>>& matrix);
	void CalculateBasinSize(ValueLocationMatrix lowPoint, std::vector<std::vector<int>>& matrix, std::vector<ValueLocationMatrix>& elementsInBasin);
};