#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main() {
	std::vector<std::string> grid;
	
	std::ifstream inFile("input.txt");
	std::string line;
	while (std::getline(inFile, line)) {
		grid.push_back(line);
	}
	inFile.close();
	size_t gridLen = grid.size();

	//Part 1
	size_t splits = 0;
	std::stack<std::pair<size_t, size_t>> beams;
	beams.push(std::make_pair(grid[0].find('S'), 0));

	while (!beams.empty()) {
		std::pair<size_t, size_t> current = beams.top();	
		beams.pop();

		bool found = false;
		while (!found && current.second < gridLen - 1) {
			grid[current.second][current.first] == '^' ? found = true : current.second += 1;
		}

		if (found) {
			grid[current.second - 1][current.first] = '|';

			if (grid[current.second][current.first + 1] != '|') {
				grid[current.second][current.first + 1] = '|';
				beams.push(std::make_pair(current.first + 1, current.second));
			}
			if (grid[current.second][current.first - 1] != '|') {
				grid[current.second][current.first - 1] = '|';
				beams.push(std::make_pair(current.first - 1, current.second));
			}
		}
	}

	for (int i = 1; i < grid.size(); ++i) {
		for (int j = 1; j < grid[i].length(); ++j) {
			if (grid[i][j] == '^' && grid[i - 1][j] == '|') {
				++splits;
			}
		}
	}

	//Part 2
	long timelines = 0;
	std::vector<long> scanner(grid[0].length(), 0);
	scanner[grid[0].find('S')] += 1;

	for (size_t i = 0; i < gridLen; ++i) {
		size_t lineSize = grid[i].size();
		for(size_t j = 1; j < lineSize - 1; ++j) {
			if (grid[i][j] == '^') {
				scanner[j + 1] += scanner[j];
				scanner[j - 1] += scanner[j];
				scanner[j] = 0;
			}
		}
	}

	for (long totalPaths : scanner) {
		timelines += totalPaths;
	}

	std::cout << "The total amount of times the beam split: " << splits << '\n';
	std::cout << "The total amount of timelines created: " << timelines << '\n';

	return 0;
}
