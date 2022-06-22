#include "Node.h"

Node::Node()
{
	parent = std::make_pair(-1, -1);
	walkable = true;
	fCost = 0;
	gCost = 0;
	hCost = 0;
	nodePosition = std::make_pair(-1, -1);
}

Node::Node(bool isWalkable, int f, int g, int h, std::pair<int, int> pos)
{
	walkable = isWalkable;
	fCost = f;
	gCost = g;
	hCost = h;
	nodePosition = pos;
}

std::pair<int, int> Node::GetParent()
{
	return parent;
}

int Node::GetWalkable()
{
	return walkable;
}

int Node::GetFCost()
{
	return gCost+hCost;
}

int Node::GetGCost()
{
	return gCost;
}

int Node::GetHCost()
{
	return hCost;
}

std::pair<int, int> Node::GetNodePosition()
{
	return nodePosition;
}

void Node::SetParent(std::pair<int, int> position)
{
	parent = position;
}

void Node::SetWalkable(bool isWalkable)
{
	walkable = isWalkable;
}

void Node::SetFCost(int newFCost)
{
	fCost = newFCost;
}

void Node::SetGCost(int newGCost)
{
	gCost = newGCost;
}

void Node::SetHCost(int newHCost)
{
	hCost = newHCost;
}

void Node::SetNodePosition(std::pair<int, int>position)
{
	nodePosition = position;
}

bool Node::operator==(const Node& secondNode)
{
	if (this->nodePosition.first == secondNode.nodePosition.first && this->nodePosition.second == secondNode.nodePosition.second && this->walkable == secondNode.walkable) {
		return true;
	}
	return false;
}

Node Node::operator=(const Node& node)
{
	this->parent = node.parent;
	this->walkable = node.walkable;
	this->fCost = node.fCost;
	this->gCost = node.gCost;
	this->hCost = node.hCost;
	this->nodePosition = node.nodePosition;

	return *this;
}