#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <cmath>
#include <limits>
#include <queue>
#include <set>

std::pair<size_t, size_t> createConnection(const std::vector<std::vector<float>>& grid, const size_t numOfCoords) {
	
	std::pair<size_t, size_t> smallest;
	float smallestDistance = std::numeric_limits<float>::max();

	for (size_t x = 0; x < numOfCoords; ++x) {
		for (size_t y = x; y < numOfCoords; ++y) {
			float current = grid[x][y];
			if (current > 0 && current < smallestDistance) {
				smallestDistance = current;
				smallest.first = x;
				smallest.second = y;
			}
		}
	}
		
	return smallest;
}

size_t threeLargestCircuts(const std::set<std::pair<size_t, size_t>>& connections) {
	std::set<size_t> seen;
	std::queue<size_t> bfs;
	size_t first = 0;
	size_t second = 0;
	size_t third = 0;

	for (std::pair<size_t, size_t> edge1 : connections) {
		size_t circutSize = 1;
		
		if (seen.count(edge1.first) == 0) {
			seen.insert(edge1.first);
			bfs.push(edge1.first);

			while (!bfs.empty()) {
				size_t current = bfs.front();
				bfs.pop();

				for (std::pair<size_t, size_t> edge2 : connections) {
					if (edge2.first = current && seen.count(edge2.second) == 0) {
						++circutSize;
						seen.insert(edge2.second);
						bfs.push(edge2.second);

					} else if (edge2.second = current && seen.count(edge2.first) == 0) {
						++circutSize;
						seen.insert(edge2.first);
						bfs.push(edge2.first);
					}
				}
			}
		}
			
		if (circutSize > first) {
			third = second;
			second = first;
			first = circutSize;
		} else if (circutSize > second) {
			third = second;
			second = circutSize;
		} else if (circutSize > third) {
			third = circutSize;
		}
	}

	return first * second * third;
}

std::pair<size_t, size_t> completeCircut(const std::vector<std::vector<float>>& grid
		, const std::set<std::pair<size_t, size_t>>& connections, const size_t numOfCoords) {


	return {0, 0};
}

int main() {
	std::ifstream inFile("input.txt"); 
	std::vector<std::tuple<int, int, int>> coords;
	std::string line;

	while (std::getline(inFile, line)) {
		size_t comma1 = line.find(',');
		size_t comma2 = line.rfind(',');
		coords.push_back(std::make_tuple(std::stoi(line.substr(0, comma1))
						,std::stoi(line.substr(comma1 + 1, comma2))
						,std::stoi(line.substr(comma2 + 1, line.length() - 1 - comma2))));
	}
	inFile.close();

	size_t numOfCoords = coords.size();
	std::vector<std::vector<float>> grid(numOfCoords);
	for (size_t i = 0; i < numOfCoords; ++i) {
		grid[i].reserve(numOfCoords);
	}

	for (size_t i = 0; i < numOfCoords; ++i) {
		for (size_t j = i; j < numOfCoords; ++j) {
			float x1 = std::get<0>(coords[i]);
			float y1 = std::get<1>(coords[i]);
			float z1 = std::get<2>(coords[i]);
			float x2 = std::get<0>(coords[j]);
			float y2 = std::get<1>(coords[j]);
			float z2 = std::get<2>(coords[j]);

			float distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			grid[i][j] = distance;
			grid[j][i] = distance;
		}
	}


	std::set<std::pair<size_t, size_t>> connections;

	//Part 1
	size_t multiple1 = 0;
	{
		std::set<std::pair<size_t, size_t>> seenEdges;
		for (int i = 0; i < 1000; ++i) {
			std::pair<size_t, size_t> edge = createConnection(grid, numOfCoords);
			connections.insert(edge);
		}
		multiple1 = threeLargestCircuts(connections);

	}

	//Part 2
	size_t multiple2 = 0;
	/*
	bool complete = false;	
	while (!complete) {
		std::pair<size_t, size_t> result = completeCircut(grid, connections, numOfCoords);

		if (result.first != 0 && result.second != 0) {
			complete = true;
			multiple2 = result;
		else {
			createConnection(grid, connections, numOfCoords);
		}
	}
	*/
	
	std::cout << "The product of the three largest circuts after 1000 connections is: " << multiple1 << '\n';
	std::cout << "The product of the final two verticies of the spanning tree is: " << multiple2 << '\n';

	return 0;
}

//THIS COMMENTED OUT CODE WAS PART 1 FULLY COMPLETED
//175440 was the part 1 answer
/*
int main() {
	std::ifstream inFile("input.txt"); 
	std::vector<std::tuple<int, int, int>> coords;
	std::string line;

	while (std::getline(inFile, line)) {
		size_t comma1 = line.find(',');
		size_t comma2 = line.rfind(',');
		coords.push_back(std::make_tuple(std::stoi(line.substr(0, comma1))
						,std::stoi(line.substr(comma1 + 1, comma2))
						,std::stoi(line.substr(comma2 + 1, line.length() - 1 - comma2))));
	}
	inFile.close();

	size_t numOfCoords = coords.size();
	std::vector<std::vector<float>> grid(numOfCoords);
	for (size_t i = 0; i < numOfCoords; ++i) {
		connections[i].reserve(numOfCoords);
	}

	for (size_t i = 0; i < numOfCoords; ++i) {
		for (size_t j = i; j < numOfCoords; ++j) {
			float x1 = std::get<0>(coords[i]);
			float y1 = std::get<1>(coords[i]);
			float z1 = std::get<2>(coords[i]);
			float x2 = std::get<0>(coords[j]);
			float y2 = std::get<1>(coords[j]);
			float z2 = std::get<2>(coords[j]);
			std::cout << x1 << ", " << y1 << ", " << z1 << '\n';

			float distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
			connections[i][j] = distance;
			connections[j][i] = distance;
		}
	}

	for (int i = 0; i < 1000; ++i) {
		std::pair<size_t, size_t> smallest;
		float smallestDistance = std::numeric_limits<float>::max();

		for (size_t x = 0; x < numOfCoords; ++x) {
			for (size_t y = x; y < numOfCoords; ++y) {
				float current = connections[x][y];
				if (current > 0 && current < smallestDistance) {
					smallestDistance = current;
					smallest.first = x;
					smallest.second = y;
				}
			}
		}

		connections[smallest.first][smallest.second] = -1;
		connections[smallest.second][smallest.first] = -1;
	}
	
	size_t first = 0;
	size_t second = 0;
	size_t third = 0;

	for (size_t i = 0; i < numOfCoords; ++i) {
		for (size_t j = i; j < numOfCoords; ++j) {
			size_t circutSize = 1;

			std::cout << i << ", " << j << '\n';
			if (connections[i][j] == -1) {
				std::set<size_t> seen;
				std::queue<size_t> bfs;

				seen.insert(i);
				seen.insert(j);
				bfs.push(i);
				bfs.push(j);
				connections[i][j] = 0;
				connections[j][i] = 0;
				++circutSize;

				while (!bfs.empty()) {
					size_t current = bfs.front();
					bfs.pop();
					for (size_t n = 0; n < numOfCoords; ++n) {
						if (connections[current][n] == -1) {
							connections[current][n] = 0;
							connections[n][current] = 0;
							if (seen.count(n) == 0) {
								seen.insert(n);
								bfs.push(n);
								++circutSize;
							}
						}
					}
				}
			}

			if (circutSize > first) {
				third = second;
				second = first;
				first = circutSize;
			} else if (circutSize > second) {
				third = second;
				second = circutSize;
			} else if (circutSize > third) {
				third = circutSize;
			}
		}
	}

	std::cout << "The multiple of the three largest circuts after 1000 connections is: "
		<< first * second * third << '\n';
	//std::cout << "The product of the final two verticies of the tree is: " << x1 * x2 << '\n';

	return 0;
}
*/
