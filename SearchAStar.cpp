//Bethany Walker
#include "SearchAStar.h"
#include <iostream>

bool compareScore(unique_ptr<SNode>& lhs, unique_ptr<SNode>& rhs)
{
	return lhs->score < rhs->score;
}

void CSearchAStar::addNewNode(TerrainMap& terrain, NodeList& openList, NodeList& closedList, bool& onList, unique_ptr <SNode>& current, unique_ptr <SNode>& goal, int xModifier, int yModifier)
{
	unique_ptr <SNode> temp(new SNode);

	temp->x = current->x + xModifier;
	temp->y = current->y + yModifier;

	int hDistanceToGoal = 0;
	onList = false;

	if (temp->x >= 0 && temp->y >= 0 && temp->x < terrain[0].size() && temp->y < terrain.size())
	{
		if (terrain[temp->y][temp->x] != 0)
		{

			hDistanceToGoal = (abs(goal->x - temp->x) + abs(goal->y - temp->y));
			temp->cost = current->cost + terrain[temp->y][temp->x];
			temp->score = temp->cost + hDistanceToGoal;
			temp->parent = current.get();

			if (openList.size() > 0)
			{
				for (int i = 0; i < openList.size(); i++)
				{
					if (openList[i]->x == temp->x)
					{
						if (openList[i]->y == temp->y)
						{
							if (openList[i]->cost >= temp->cost)
							{
								openList[i]->parent = temp->parent;
								openList[i]->cost = temp->cost;

								openList[i]->score = temp->score;
							}
							onList = true;
							break;
						}
					}
				}
			}

			if (closedList.size() > 0)
			{
				for (int i = 0; i < closedList.size(); i++)
				{
					if (closedList[i]->x == temp->x)
					{
						if (closedList[i]->y == temp->y)
						{
							if (closedList[i]->cost >= temp->cost)
							{
								closedList[i]->parent = temp->parent;
								closedList[i]->cost = temp->cost;

								closedList[i]->score = temp->score;
								openList.push_back(move(closedList[i]));					

							}
							onList = true;
							break;
						}
					}
				}
			}


			if (!onList)
			{
				openList.push_back(move(temp));
			}
		}
	}
}

bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	unique_ptr <SNode> current(new SNode);
	bool found = false;
	int timesSorted = 0;

	NodeList openList;
	NodeList closedList;

	int westX = -1;
	int northY = 1;
	int eastX = 1;
	int southY = -1;

	int hDistanceToGoal = (abs(goal->x - start->x) + abs(goal->y - start->y));
	start->cost = terrain[start->y][start->x];
	start->score = hDistanceToGoal + terrain[start->y][start->x];

	openList.push_back(move(start));

	do
	{
		if (openList.size() <= 0)
		{
			return false;
		}

		if (openList.size() > 1)
		{
			sort(openList.begin(), openList.end(), compareScore);
			timesSorted++;
		}

		current = move(openList.front());
		openList.pop_front();


		if (current->x == goal->x)
		{
			if (current->y == goal->y)
			{
				goal->parent = current.get()->parent;
				found = true;
				break;
			}
		}
		bool onList = false;

		addNewNode(terrain, openList, closedList, onList, current, goal, westX, 0);
		addNewNode(terrain, openList, closedList, onList, current, goal, 0, northY);
		addNewNode(terrain, openList, closedList, onList, current, goal, eastX, 0);
		addNewNode(terrain, openList, closedList, onList, current, goal, 0, southY);

		closedList.push_back(move(current));

	} while (!found);



	path.push_front(move(goal));


	
	unique_ptr <SNode> currentParent;

	do
	{
		if (closedList.size() > 0)
		{
			for (int i = 0; i < closedList.size(); i++)
			{
				if (closedList[i] == NULL) break;
				if (path.front()->parent == NULL) break;
				if (path.front()->parent->x == closedList[i]->x && path.front()->parent->y == closedList[i]->y)
				{
					path.push_front(move(closedList[i]));
				}
			}
		}
		else
		{
			break;
		}


	} while (path.front()->parent != nullptr);

	

	return true;
}
