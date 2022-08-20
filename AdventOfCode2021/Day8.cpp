#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Day8.h"
#include "Functions.h"

void Day8::Solve() {

	//be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
	//edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
	//fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
	//fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
	//aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
	//fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
	//dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
	//bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
	//egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
	//gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce


	// In the output values, how many times do digits 1, 4, 7, or 8 appear ?

	Functions f;

	std::ifstream inputFile("Day8.input");
	std::string aux = "";
	std::vector<std::string> splitResultString1;
	std::vector<std::string> splitResultString2;
	std::vector<std::string> uniqueSignal;
	std::vector<std::string> digitOutput;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, aux))
		{
			splitResultString1 = f.SplitStr(aux, "|");

			splitResultString2 = f.SplitStr(splitResultString1[1], " ");
			for (auto&& element : splitResultString2) {
				if (element != "") {
				digitOutput.push_back(element);
				}
			}
		}
	}

	int output = 0;
	for (auto&& element : digitOutput) {
		if (element.size() == 2 || element.size() == 4 || element.size() == 3 || element.size() == 7) {
			output++;
		}
	}

	std::cout << "The digits 1,4,7 and 8 apear " << output << " times in the output" << std::endl;
}