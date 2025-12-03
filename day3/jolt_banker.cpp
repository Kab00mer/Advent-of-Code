#include <iostream>
#include <fstream>
#include <unordered_map>

int main() {
	std::ifstream inFile("input.txt");
	std::string line;
	std::unordered_map<size_t, size_t> leftMost;
	std::unordered_map<size_t, size_t> rightMost;
	size_t bankedJoltage = 0;

	while (std::getline(inFile, line)) {	
		for (size_t i = 0; i <= 9; ++i) {
			leftMost[i] = 100;
			rightMost[i] = 0;
		}

		size_t len = line.length();
		for (size_t i = 0; i < len; ++i) {
			leftMost[line[len - 1 - i] - '0'] = len - 1 - i;
			rightMost[line[i] - '0'] = i;
		}
		
		short tensDigit = 9;
		short onesDigit = 9;
		bool foundLargest = false;
		while (!foundLargest && tensDigit >= 0) {

			while (!foundLargest && onesDigit >= 0) {
				leftMost[tensDigit] < rightMost[onesDigit] ? foundLargest = true : --onesDigit;
			}

			if(!foundLargest) {
				onesDigit = 9;
				--tensDigit;
			}
		}

		bankedJoltage += tensDigit * 10 + onesDigit;

		leftMost.clear();
		rightMost.clear();
	}
	
	inFile.close();

	std::cout << "The maximum joltage of all banks is: " << bankedJoltage << '\n';
}
