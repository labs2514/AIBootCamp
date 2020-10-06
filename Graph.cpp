#include "Graph.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <InitData.h>

using namespace std;

Graph::Graph(const SInitData& _init)
{
	_nbTiles = _init.tileInfoArraySize;
	_maxTurns = _init.maxTurnNb;
	for_each(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& tile)
	{
		// Ignore forbidden cells
		if (tile.type != Forbidden)
		{
			// Add to vector of goals
			if (tile.type == Goal) {
				_goals.push_back(STileCoord{ tile.q, tile.r });
			}

			vector<STileCoord> neighbors;
			STileCoord coord = { tile.q, tile.r };

			// Potential neighbor
			STileCoord neighbor;

			//NE case
			neighbor = { tile.q - 1, tile.r + 1 };
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == NE); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == SW); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}					
			}

			//E case
			neighbor = { tile.q , tile.r + 1 };
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == E); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == W); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//SE case
			neighbor = { tile.q + 1, tile.r };
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == SE); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == NW); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//SW case
			neighbor = { tile.q + 1, tile.r - 1 };
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == SW); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == NE); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//W case
			neighbor = { tile.q , tile.r - 1};
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == W); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == E); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//NW case
			neighbor = { tile.q - 1, tile.r };
			if (find_if(_init.tileInfoArray + 0, _init.tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= _init.tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == NW); })
					== _init.objectInfoArray + _init.objectInfoArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(_init.objectInfoArray + 0, _init.objectInfoArray + _init.objectInfoArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == SE); })
						== _init.objectInfoArray + _init.objectInfoArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			_graph[coord] = neighbors;
			_cellUsedBy[coord] = -1;
		}
	});
}

vector<STileCoord> Graph::astarPath(STileCoord start, STileCoord goal)
{
	bool pathFound = false;
	priority_queue<pair<int, STileCoord>, vector<pair<int, STileCoord>>, greater<pair<int, STileCoord>>> queue;
	queue.emplace(0, start);

	map<STileCoord, STileCoord> cameFrom;
	map<STileCoord, int> costSoFar;

	cameFrom[start] = start;
	costSoFar[start] = 0;
		
	while (!queue.empty())
	{
		// Pas de chemin possible
		if (queue.top().first > _maxTurns) {
			return vector<STileCoord>{};
		}

		STileCoord current = queue.top().second;
		queue.pop();

		if (current == goal)
		{
			pathFound = true;
			break;
		}

		for (STileCoord next : _graph[current])
		{
			int newCost = costSoFar[current] + 1;
			if (costSoFar.find(next) == end(costSoFar) || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priority = newCost + heuristic(next, goal);
				queue.emplace(priority, next);
				cameFrom[next] = current;
			}				
		}
	}

	vector<STileCoord> path;
	
	if (pathFound)
	{
		STileCoord current = goal;
		while (current != start)
		{
			path.push_back(current);
			current = cameFrom[current];
		}
		path.push_back(start);
		reverse(begin(path), end(path));
	}

	return path;
}

vector<STileCoord> Graph::getBestPath(STileCoord start)
{
	vector<STileCoord> bestPath{_maxTurns+1};
	for (int i = 0; i < _goals.size(); i++)
	{
		vector<STileCoord> path = astarPath(start, _goals[i]);
		if (!path.empty() && path.size() < bestPath.size())
		{
			bestPath = path;
		}
	}

	if (bestPath.size() > _maxTurns) {
		bestPath.clear();
	}

	return bestPath;
}

void Graph::reserveGoal(STileCoord goal)
{
	_goals.erase(find(begin(_goals), end(_goals), goal));
}

void Graph::returnGoal(STileCoord goal)
{
	_goals.push_back(goal);
}


void Graph::lockCell(STileCoord cell)
{
	_graph.erase(_graph.find(cell));
	
	for_each(begin(_graph), end(_graph), [cell](auto & p)
		{
			vector<STileCoord>& neighbors = p.second;
			vector<STileCoord>::iterator ite = find(begin(neighbors), end(neighbors), cell);
			if (ite != end(neighbors))
			{
				neighbors.erase(ite);
			}
		});
		
}

int Graph::heuristic(STileCoord& a, STileCoord& b)
{
	return (abs(a.first - b.first) + abs(a.first + a.second - b.first - b.second) + abs(a.second - b.second))/2;
}