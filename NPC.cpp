#include "NPC.h"
#include <algorithm>

SOrder NPC::getOrder()
{
	if (_path.empty())	// TODO : QUESTIONNABLE
		return SOrder{ EOrderType::Move, _uid, EHexCellDirection::CENTER };

	auto pathPos = find(_path.begin(), _path.end(), getPos());
	
	if(next(pathPos) != _path.end())
		return SOrder{ EOrderType::Move, _uid, getDirection(*pathPos, *(next(pathPos))) };	// Continue
	else
		return SOrder{ EOrderType::Move, _uid, EHexCellDirection::CENTER };	// End of path, wait. (QUESTIONNABLE)
}

EHexCellDirection NPC::getDirection(STileCoord from, STileCoord to)
{
	int q = to.first - from.first;
	int r = to.second - from.second;

	return DIRECTION[q + 1][r + 1];
}