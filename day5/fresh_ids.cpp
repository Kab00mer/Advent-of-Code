#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream inFile("input.txt");
	std::string line;
	std::vector<std::pair<long, long>> validIds;
	size_t size = 190;
	validIds.reserve(size);

	for (int i = 0; i < size; ++i) {
		std::getline(inFile, line);
		size_t len = line.length();
		size_t divider = 0;

		{
			size_t counter = 0;
			while (counter < len && divider == 0) {
				if (line[counter] == '-') {
					divider = counter;
				}
				++counter;
			}
		}

		validIds.emplace_back(std::make_pair(std::stol(line.substr(0, divider)),
					std::stol(line.substr(divider + 1, len  - 1 - divider))));
	}

	// ---- THIS SECTION IS PART 1 ----
	std::getline(inFile, line);
	size_t freshIds1 = 0;

	while (std::getline(inFile, line)) {
		long produce = std::stol(line);
		bool found = false;
		size_t i = 0;
		while (!found && i < size) {
			if (produce >= validIds[i].first && produce <= validIds[i].second) {
				found = true;
				++freshIds1;
			} else {
				++i;
			}
		}
	}
	
	inFile.close();

	// ---- THIS SECTION IS PART 2 ----	
	size_t freshIds2 = 0;

	for (size_t i = 0; i < size; ++i) {
		long start1 = validIds[i].first;
		long end1 = validIds[i].second;

		bool rangeMerged = false;
		for (size_t j = i + 1; j < size; ++j) {
			long start2 = validIds[j].first;
			long end2 = validIds[j].second;

			bool overlap =  (end1 >= start2 && end1 <= end2) || (end2 >= start1 && end2 <= end1) 
				|| (start1 >= start2 && start1 <= end2) || (start2 >= start1 && start2 <= end1);

			if (overlap) {
				start1 = start1 < start2 ? start1 : start2;
				end1 = end1 > end2 ? end1 : end2;

				validIds.erase(validIds.begin() + j);
				--j;
				--size;
				rangeMerged = true;
			}
		}

		if (rangeMerged) {
			validIds[i].first = start1;
			validIds[i].second = end1;
			--i;
		} else {
			freshIds2 += end1 - start1 + 1;
		}
	}

	std::cout << "The total number of fresh ids for part 1 is: " << freshIds1 << '\n';
	std::cout << "The total number of fresh ids for part 2 is: " << freshIds2 << '\n';
	return 0;
}
