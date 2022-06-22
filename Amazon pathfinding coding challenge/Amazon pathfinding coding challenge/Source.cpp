//we're going to use A* algorithm in order to determine the shortest path to our destination
//g cost->distance from starting node
//h cost->distance form end node
//f cost->g cost + h cost
//
//if are multiple minimum f cost values that are equal we select the one which is closest to the end node

#include<iostream>
#include"Map.h"

int main() 
{
	int height, width, option = 0, obstacleCount = 0;
	std::pair<int, int> startPos, finishPos;

	std::cout << "Please introduce map dimensions:\n";

	std::cout << "Height:";
	std::cin >> height;

	std::cout << "Length:";
	std::cin >> width;

	std::cout << std::endl;

	std::cout << "Please introduce start position:\n";

	std::cout << "X:";
	std::cin >> startPos.first;

	std::cout << "Y:";
	std::cin >> startPos.second;

	std::cout << std::endl;

	std::cout << "Please introduce delivery position:\n";

	std::cout << "X:";
	std::cin >> finishPos.first;

	std::cout << "Y:";
	std::cin >> finishPos.second;

	Map map(height, width, startPos, finishPos);

	map.PrintDetails();

	std::cout << "How do you want to find the shortest path?\n";

	std::cout << "1. Without any obstacles\n";
	std::cout << "2. With obstacles\n";
	std::cout << "Select your option: "; std::cin >> option;

	while (option != 1 && option != 2) {
		std::cout << "\nPlease select a valid option(1 or 2): \n";
		std::cout << "Select your option: "; std::cin >> option;
	}
	if (option == 1) {
		map.FindPath(startPos, finishPos);
	}
	else {
		std::cout << "\nIntroduce number of obstacles: "; std::cin >> obstacleCount;
		while (obstacleCount < 0 || obstacleCount>height * width - 2) {
			std::cout << "\nPlease select a valid obstacle number: \n";
			std::cout << "Number of obstacles: "; std::cin >> obstacleCount;
		}
		map.GenerateRandomObstacles(obstacleCount);
		map.FindPath(startPos, finishPos);
	}

}