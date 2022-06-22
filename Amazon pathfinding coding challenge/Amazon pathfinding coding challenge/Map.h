#pragma once
#include<iostream>
#include<vector>
#include "Node.h"

class Map
{
public:
	Map(int, int, std::pair<int, int>, std::pair<int, int>);

	bool IsPositionValid(std::pair<int, int>);
	bool AreDifferentPositions(std::pair<int, int>, std::pair<int, int>);

	void PrintDetails();
	std::vector<Node> eraseFromVector(std::vector<Node>, std::pair<int, int>);

	std::vector<Node> GetNeighbours(Node);
	int GetDistance(Node, Node);
	void FindPath(std::pair<int, int>, std::pair<int, int>);
	void RetracePath(Node, Node);
	void GenerateRandomObstacles(int);

private:
	int mapHeight, mapWidth;
	std::pair<int, int> startPos, finishPos;
	std::vector<std::vector<Node>> grid;
};