#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const size_t NUM_OF_TERMS = 4;

int main() {
	std::ifstream inFile("input.txt");
	std::string line;
	std::vector<std::string> terms;
	long total = 0;

	while (std::getline(inFile, line)) {
		size_t lineLen = line.length();
		std::string current = "";
		bool justInSpace = false;
		bool justInTerm = true;

		for (int i = 0; i < lineLen - 1; ++i) {
			char ch = line[i];

			if (ch == ' ') {
				justInSpace = true;
				if (justInTerm) {
					justInTerm = false;
				} else {
					current.push_back(ch);
				}

			} else if (ch == '+' || ch == '*') {
				

			} else if (justInSpace) {
				justInSpace = false;		
				justInTerm = true;
				terms.push_back(current.substr(0, current.length() - 1));
				current = {ch};

			} else {
				current.push_back(ch);
			}
		}
	}

	for (auto s : terms) {
		std::cout << s << '\n';
	}

	inFile.close();
	std::cout << "The grand total of all cephalopod math problems in part2 is: " << total << '\n';
	return 0;
}
