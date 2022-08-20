#include <iostream>
#include <string>
#include <chrono>
//#include "Day1.h"
//#include "Day2.h"
//include "Day3.h"
//#include "Day4.h"
//#include "Day5.h"
//#include "Day6.h"
//#include "Day7.h"
//#include "Day8.h"
#include "Day9.h"
	
int main() {

	auto start = std::chrono::high_resolution_clock::now();
	Day9 d;
	d.Solve();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Solved in " << duration.count() << " ms.\n\n";
}