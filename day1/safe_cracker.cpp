#include <iostream>
#include <fstream>

int main() {
	int currentTick = 50;
	int totalStops = 0;
	int totalClicks = 0;

	std::ifstream inFile("input.txt");
	std::string line;
	while (getline(inFile, line)) {
		int amount = std::stoi(line.substr(1, line.length() - 1));		
		if (line[0] == 'L') {
			if (currentTick == 0) --totalClicks;

			currentTick -= amount;
			while (currentTick < 0) {
				currentTick += 100;
				++totalClicks;
			}

		} else {

			currentTick += amount;
			if (currentTick % 100 == 0) --totalClicks;

			while (currentTick > 99)  {
				currentTick -= 100;
				++totalClicks;
			}
		}
	
		if (currentTick == 0) ++totalStops;
	}
	inFile.close();

	std::cout << "Zero's Stops: " << totalStops << '\n';
	std::cout << "Zero's Clicks: " << totalClicks << '\n';
	std::cout << "Zero's Clicks and Stops: " << (totalStops + totalClicks) << '\n';

	return 0;
}
