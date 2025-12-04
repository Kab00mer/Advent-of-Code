#include <iostream>
#include <fstream>
#include <set>

const size_t MATRIX_SIZE = 140;

const std::pair<size_t, size_t> ADJACENT_NEIGHBORS[] = {
	{1, 0},
	{1, 1},
	{0, 1},
	{-1, 1},
	{-1, 0},
	{-1, -1},
	{0, -1},
	{1, -1}
};

int main() {
	std::string lines[MATRIX_SIZE];
	{
		std::ifstream inFile("input.txt");
		std::string line;
		size_t count = 0;
		while (std::getline(inFile, line)) {
				lines[count] = line;
				++count;
		}
		inFile.close();
	}

	size_t paperRolls = 0;
	bool finished = false;
	while (!finished) {
		std::set<std::pair<size_t,size_t>> foundRolls;	
		size_t currentPaperRolls = 0;

		for (int x = 0; x < MATRIX_SIZE; ++x) {
			for(int y = 0; y < MATRIX_SIZE; ++y) {
				if (lines[x][y] == '@') {
					size_t neighborCount = 0;
					size_t i = 0;
					while (neighborCount < 4 && i < 8) {
						int xPos = x + ADJACENT_NEIGHBORS[i].first;
						int yPos = y + ADJACENT_NEIGHBORS[i].second;
						if (xPos < MATRIX_SIZE && xPos >= 0 && yPos < MATRIX_SIZE && yPos >= 0 
								&& lines[xPos][yPos] == '@'){
							++neighborCount;
						}
						++i;
					}

					if (neighborCount < 4) {
						foundRolls.insert(std::pair(x, y));
						++currentPaperRolls;
					}
				}
			}
		}

		for (std::pair<size_t,size_t> coord : foundRolls) {
			lines[coord.first][coord.second] = '.';
		}

		currentPaperRolls == 0 ? finished = true : paperRolls += currentPaperRolls;
	}

	std::cout << "The number of accessable paper rolls is: " << paperRolls << '\n';

	return 0;
}
