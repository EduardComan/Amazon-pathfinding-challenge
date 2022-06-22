#include<iostream>
#include<unordered_set>
#include<set>
#include<vector>
#include<cmath>
#include<random>
#include"Map.h"
#include"Node.h"

Map::Map(int height, int width, std::pair<int, int>start, std::pair<int, int>finish)
{
	try {
		if (height > 0 && width > 0) {
			mapHeight = height;
			mapWidth = width;
		}
		else {
			throw std::invalid_argument("Map dimensions should be greater than 0!");
		}

		if (IsPositionValid(start) && IsPositionValid(finish) && AreDifferentPositions(start, finish)) {
			startPos = start;
			finishPos = finish;
		} 
		else {
			throw std::invalid_argument("Start and finish positions are not valid!");
		}

		Node emptyNode();

		grid.resize(mapHeight);

		for (int i = 0; i < mapHeight; i++) {
			grid[i].resize(mapWidth);
		}

		for (int i = 0; i < mapHeight; i++) {
			for (int j = 0; j < mapWidth; j++) {
				grid[i][j].SetNodePosition(std::make_pair(i, j));
			}
		}
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}
}

bool Map::IsPositionValid(std::pair<int, int>pos)
{
	if ((pos.first >= 0 && pos.first <= mapHeight) && (pos.second >= 0 && pos.second <= mapWidth))
		return true;

	return false;
}

bool Map::AreDifferentPositions(std::pair<int, int> firstPos, std::pair<int, int> secondPos)
{
	if (firstPos.first == secondPos.first && firstPos.second == secondPos.second)
		return false;

	return true;
}

void Map::PrintDetails()
{
	std::cout << "Map details: ";
	std::cout << "Height: " << mapHeight << " Width: " << mapWidth << std::endl;

	std::cout << "Start position: ";
	std::cout << "X: " << startPos.first << " Y: " << startPos.second << std::endl;

	std::cout << "Delivery position: ";
	std::cout << "X: " << finishPos.first << " Y: " << finishPos.second << std::endl << std::endl;
}

std::vector<Node> Map::eraseFromVector(std::vector<Node> vect, std::pair<int, int> pos)
{
	for (int i = 0;i < vect.size();i++) {
		if (vect[i].GetNodePosition().first == pos.first && vect[i].GetNodePosition().second == pos.second) {
			vect.erase(vect.begin() + i);
		}
	}

	return vect;
}

std::vector<Node> Map::GetNeighbours(Node node)
{
	std::vector<Node> neighbours;

	//looping through 3x3 size neghbours
	for (int x = -1; x <= 1;x++) {
		for (int y = -1; y <= 1;y++) {
			//skipping the middle one because it is our current node
			if (x == 0 && y == 0) {
				continue;
			}

			int checkX = node.GetNodePosition().first + x;
			int checkY = node.GetNodePosition().second + y;

			//adding the nodes if they are on the grid
			if (checkX >= 0 && checkX < mapHeight && checkY >= 0 && checkY < mapWidth) {
				neighbours.push_back(grid[checkX][checkY]);
			}
		}
	}

	return neighbours;
}

int Map::GetDistance(Node firstNode, Node secondNode)
{
	int distanceX = abs(firstNode.GetNodePosition().first - secondNode.GetNodePosition().first);
	int distanceY = abs(firstNode.GetNodePosition().second - secondNode.GetNodePosition().second);

	if (distanceX > distanceY) {
		return 14 * distanceY + 10 * (distanceX - distanceY);
	}

	return 14 * distanceX + 10 * (distanceY - distanceX);
}

void Map::FindPath(std::pair<int, int> startPosition, std::pair<int, int> deliveryPosition)
{
	Node startNode = grid[startPos.first][startPos.second];
	Node finishNode = grid[finishPos.first][finishPos.second];

	std::vector<Node> openSet;
	std::vector<Node> closeSet;

	openSet.push_back(startNode);

	while (openSet.size() > 0) {
		Node currentNode = openSet[0];
		
		//determine node with lowest fCost
		for (int i = 1; i < openSet.size(); i++) {
			if (openSet[i].GetFCost() < currentNode.GetFCost() || openSet[i].GetFCost() == currentNode.GetFCost() && openSet[i].GetHCost() < currentNode.GetHCost()) {
				currentNode = openSet[i];
			}
		}

		openSet = eraseFromVector(openSet, std::make_pair(currentNode.GetNodePosition().first, currentNode.GetNodePosition().second));
		closeSet.push_back(currentNode);

		//check if we found the destination node
		if (currentNode == finishNode) {
			RetracePath(startNode, finishNode);
			return;
		}

		//loop through neighbours
		/*std::vector<Node> vect = GetNeighbours(currentNode);
		if (vect.size() == 0) continue;*/
		for(Node neighbour : GetNeighbours(currentNode)) {
			Node usedNeighbour = grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second];

			//check if neighbour is not walkable or if it is in the closed list
			if (usedNeighbour.GetWalkable() == false || std::find(closeSet.begin(), closeSet.end(), usedNeighbour) != closeSet.end()) {
				continue;
			}

			int newMovementCostToNeighbour = currentNode.GetGCost() + GetDistance(currentNode, usedNeighbour);
			if (newMovementCostToNeighbour < usedNeighbour.GetGCost() || std::find(openSet.begin(), openSet.end(), usedNeighbour) == openSet.end()) {
				//updating values for neighbours
				int GCost = newMovementCostToNeighbour;
				int HCost = (GetDistance(usedNeighbour, finishNode));
				std::pair<int, int> parent = std::make_pair(currentNode.GetNodePosition().first, currentNode.GetNodePosition().second);

				grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second].SetGCost(GCost);
				grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second].SetHCost(HCost);
				grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second].SetParent(parent);

				if (std::find(openSet.begin(), openSet.end(), grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second]) == openSet.end()) {
					openSet.push_back(grid[neighbour.GetNodePosition().first][neighbour.GetNodePosition().second]);
				}
			}
		}
	}
}

void Map::RetracePath(Node startNode, Node finishNode)
{
	std::vector<Node> path;
	std::pair<int, int> parentPos;

	Node currentNode = grid[finishNode.GetNodePosition().first][finishNode.GetNodePosition().second];

	//retracing our path
	while (!(currentNode == startNode)) {
		path.push_back(currentNode);
		parentPos = currentNode.GetParent();
		currentNode = grid[parentPos.first][parentPos.second];
	}

	//adding the first node to the path
	path.push_back(grid[startNode.GetNodePosition().first][startNode.GetNodePosition().second]);

	//getting the right order of steps
	std::reverse(path.begin(), path.end());

	//printing the path
	std::cout << "Path: [";
	for (int i = 0; i < path.size(); i++) {
		std::cout << "(" << path[i].GetNodePosition().first << ", " << path[i].GetNodePosition().second << ")";
		if (i < path.size() - 1) {
			std::cout << ", ";
		}
		else {
			std::cout << "]";
		}
	}

	//printing step numbers
	std::cout << "\nSteps: " << path.size()-1;
}

void Map::GenerateRandomObstacles(int dimension)
{
	std::vector<std::pair<int, int>> pos;
	std::pair<int, int> generatedPair;

	for (int i = 0; i < dimension; i++) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> seed1(0, mapHeight);
		std::uniform_int_distribution<> seed2(0, mapWidth);

		generatedPair = std::make_pair(seed1(gen), seed2(gen));
		grid[generatedPair.first][generatedPair.second].SetWalkable(false);
		pos.push_back(generatedPair);
	}

	//printing generated positions
	std::cout << "\nObstacle positions: [";
	for (int i = 0; i < pos.size(); i++) {
		std::cout << "(" << pos[i].first << ", " << pos[i].second << ")";
		if (i < pos.size() - 1) {
			std::cout << ", ";
		}
		else {
			std::cout << "]\n";
		}
	}
}
