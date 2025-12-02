#include <iostream>
#include <fstream>

long returnInvalidIds(unsigned long current, unsigned long end) {
	unsigned long sum = 0;

	while (current <= end) {
		std::string currentStr = std::to_string(current);
		size_t len = currentStr.size();
		
		if (len != 1) {
			size_t currentCut = 1;
			bool invalid = false;

			while (currentCut <= (len / 2) && !invalid) {
				if (len % currentCut == 0) {	
					size_t checkingPos = currentCut;
					bool symmetry = true;

					while (checkingPos < len && symmetry) {
						if (currentStr.substr(0, currentCut) != currentStr.substr(checkingPos, currentCut)) {
							symmetry = false;
						} else {
							checkingPos += currentCut;
						}
					}

					if (symmetry) invalid = true;
				}

				++currentCut;	
			}

			if (invalid) sum += current;
		}

		++current;
	}
				
	return sum;	
}

int main() {
	std::ifstream inFile("input.txt");	
	std::string input;
	std::getline(inFile, input);
	inFile.close();	

	size_t inputSize = input.size();
	size_t idDivider = 0;
	size_t parsingPos = 0;
	size_t start = 0;
	unsigned long invalidSum = 0;
	
	while (parsingPos < inputSize) {
		if (input[parsingPos] == '-') {
			idDivider = parsingPos;
		} else if (input[parsingPos] == ',') {
			unsigned long first = std::stol(input.substr(start, idDivider - start));
			unsigned long second = std::stol(input.substr(idDivider + 1, parsingPos - idDivider - 1));			
			invalidSum += returnInvalidIds(first, second);
			
			start = parsingPos + 1;
		}

		++parsingPos;
	}
	
	//One more time since we're at the end of the string
	unsigned long first = std::stol(input.substr(start, idDivider - start));
	unsigned long second = std::stol(input.substr(idDivider + 1, parsingPos - idDivider - 1));			
	invalidSum += returnInvalidIds(first, second);

	std::cout << "The sum of all invalid IDs are: " << invalidSum << '\n';

	return 0;
}
