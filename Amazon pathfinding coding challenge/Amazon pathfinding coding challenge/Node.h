#pragma once
#include<iostream>

class Node
{
public:
	Node();
	Node(bool, int, int, int, std::pair<int, int>);

	std::pair<int, int> GetParent();
	int GetWalkable();
	int GetFCost();
	int GetGCost();
	int GetHCost();
	std::pair<int, int> GetNodePosition();

	void SetParent(std::pair<int, int>);
	void SetWalkable(bool);
	void SetFCost(int);
	void SetGCost(int);
	void SetHCost(int);
	void SetNodePosition(std::pair<int, int>);

	bool operator== (const Node&);
	Node operator =(const Node&);

private:
	std::pair<int, int> parent;
	bool walkable;
	int fCost, gCost, hCost;
	std::pair<int, int> nodePosition;
};