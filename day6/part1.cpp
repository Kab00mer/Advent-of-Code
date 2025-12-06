#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const size_t NUM_OF_TERMS = 4;

int main() {
	std::ifstream inFile("input.txt");	
	std::vector<int> nums;
	long total2 = 0;

	std::string token;
	long total = 0;
	size_t opperationCounter = 0;
	while (inFile >> token) {
		if (token != "+" && token != "*") {
			nums.emplace_back(std::stoi(token));
		} else {	
			size_t size = nums.size();
			size_t counter = opperationCounter;

			long problemTotal1 = nums[counter];
			counter += size / NUM_OF_TERMS;

			while (counter < size) {
				token == "+" ? problemTotal1 += nums[counter] : problemTotal1 *= nums[counter];
				counter += size / NUM_OF_TERMS;
			}

			total += problemTotal1;
			++opperationCounter;
		}
	}

	std::cout << "The grand total of all cephalopod math problems in part1 is: " << total << '\n';
	return 0;
}
