#pragma once
#include <vector>

#include "Graph.h"

using namespace std;

class NPC
{
private:
	const EHexCellDirection DIRECTION[3][3]{ { CENTER, NW, NE },
											 { W, CENTER, E },
											 { SW, SE, CENTER } };

	int _uid = 0;
	STileCoord _pos;

	vector<STileCoord> _path{};

public:
	NPC() = default;
	NPC(int uid, STileCoord pos) : _uid{ uid }, _pos { pos } {};

	~NPC() = default;

	void setPath(vector<STileCoord> path) { _path = path; };
	vector<STileCoord> getPath() { return _path; };
	STileCoord getPos() { return _pos; };

	SOrder getOrder();
	void clearPath() { _path.clear(); };

private:
	EHexCellDirection getDirection(STileCoord from, STileCoord to);	// Changer de classe?
};