#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cmath>

long part1(const std::string& line) {
	std::unordered_map<size_t, size_t> leftMost;
	std::unordered_map<size_t, size_t> rightMost;

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

	return tensDigit * 10 + onesDigit;
}

long part2Imp1(const std::string& line) {
	//num then vector of pos
	std::unordered_map<size_t, std::vector<size_t>> leftMost;

	size_t len = line.length();
	for (size_t i = 0; i < len; ++i) {
		leftMost[line[i] - '0'].emplace_back(i);
	}

	long sum = 0;

	int n = 12;
	size_t buildingPos = 0;
	int digit = 9;	

	while (n > 0) {
		size_t size = leftMost[digit].size();
		bool found = false;
		size_t counter = 0;

		while (!found && counter < size) {
			size_t pos = leftMost[digit][counter];	
			if (pos > buildingPos && pos <= len - n) {
				//std::cout << n <<  " -> " << digit << " at pos " << pos << '\n';
				std::cout << digit << ", ";

				found = true;
				buildingPos = pos;

				--n;
				long temp = 1;
				for (size_t k = 0; k < n; ++k) {
					temp *= 10;
				}
				sum += digit * temp;

				digit = 9;
			}
			++counter;
		}

		if (!found) {
			--digit;
		}
	}
	std::cout << "AND THEIR SUM IS -> " << sum << '\n';

	return sum;
}

long part2Imp2(const std::string& line) {
	std::stack<size_t> s;
	size_t len = line.length();

	for (size_t i = 0; i < len; ++i) {
		size_t digit = line[i] - '0';

		while(!s.empty() && s.top() < digit && (s.size() - 1) + (len - i - 1) >= 12) {
			s.pop();
		}

		if (s.size() < 12) {
			s.push(digit);
		}
	}

	long result = 0;
	long digitsPlace = 1;

	for (size_t i = 0; i < 12; ++i) {
		size_t digit = s.top();
		s.pop();
		result += digit * digitsPlace;
		digitsPlace *= 10;
	}

	std::cout << result << '\n';
	return result;
}

int main() {
	std::ifstream inFile("examples.txt");
	//std::ifstream inFile("input.txt");
	std::string line;
	long bankedJoltage = 0;

	while (std::getline(inFile, line)) {
		//Sadly, I couldn't get part 2 ):
		//bankedJoltage += part1(line);
		bankedJoltage += part2Imp1(line);
		//bankedJoltage += part2Imp2(line);
	}

	inFile.close();
	std::cout << "The maximum joltage of all banks is: " << bankedJoltage << '\n';
	return 0;	
}
//170315293015051 for first implementation
//170366777461444 for second implementation
