#pragma once
#include <Globals.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <InitData.h>

using namespace std;
using STileCoord = pair<int, int>;

class Graph
{
private:
	int _nbTiles;
	vector<STileCoord> _goals;
	map<STileCoord,vector<STileCoord>> _graph;
	map<STileCoord, int> _cellUsedBy;
	// map<int, vector<STileCoord>> _paths; HERE OR NOT ?
	
public:
	Graph() = delete;
	Graph(const STileInfo* tileInfoArray, const int tileArraySize,
		  const SObjectInfo* objectInfoArray = nullptr, const int objectArraySize = 0);
	vector<STileCoord> astarPath(STileCoord start, STileCoord goal);
	vector<STileCoord> getGoals() { return _goals; };
	int getCellUser(STileCoord cell) { return _cellUsedBy[cell]; };
	void setCellUser(STileCoord cell, int uid) { _cellUsedBy[cell] = uid; };
	void lockCell(STileCoord cell);
	int heuristic(STileCoord& a, STileCoord& b) ;
};

