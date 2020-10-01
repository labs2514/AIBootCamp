#include "Graph.h"

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

Graph::Graph(const STileInfo* tileInfoArray, const int tileArraySize, const SObjectInfo* objectInfoArray, const int objectArraySize)
{
	_nbTiles = tileArraySize;
	for_each(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& tile)
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
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == NE); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == SW); })
						== objectInfoArray + objectArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}					
			}

			//E case
			neighbor = { tile.q , tile.r + 1 };
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == E); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == W); })
						== objectInfoArray + objectArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//SE case
			neighbor = { tile.q + 1, tile.r };
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == SE); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == NW); })
						== objectInfoArray + objectArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//SW case
			neighbor = { tile.q + 1, tile.r - 1 };
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == SW); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == NE); })
						== objectInfoArray + objectArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//W case
			neighbor = { tile.q , tile.r - 1};
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == W); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == E); })
						== objectInfoArray + objectArraySize)
					{
						neighbors.push_back(neighbor);
					}
				}
			}

			//NW case
			neighbor = { tile.q - 1, tile.r };
			if (find_if(tileInfoArray + 0, tileInfoArray + _nbTiles, [&](STileInfo& otherTile)
				{return (otherTile.q == neighbor.first && otherTile.r == neighbor.second && otherTile.type != Forbidden); })
				!= tileInfoArray + _nbTiles)
			{
				// Is there an obstacle on actual cell blocking path to potential neighbor
				if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
					{return (object.q == coord.first && object.r == coord.second && object.cellPosition == NW); })
					== objectInfoArray + objectArraySize)
				{
					// Is there an obstacle on neighbor cell blocking path to actual cell
					if (find_if(objectInfoArray + 0, objectInfoArray + objectArraySize, [&](SObjectInfo& object)
						{return (object.q == neighbor.first && object.r == neighbor.second && object.cellPosition == SE); })
						== objectInfoArray + objectArraySize)
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