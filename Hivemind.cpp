#include "Hivemind.h"

void Hivemind::Init(const SInitData& _initData)
{
	InitNPCs(_initData.npcInfoArray, _initData.nbNPCs);
}

void Hivemind::AStarSolution()
{
	// TODO Apr�s NPC et Graph
}

void Hivemind::PushNextOrder(std::list<SOrder>& orders)
{
	// TODO Apr�s AStar
}

void Hivemind::StopConflictingNPCs()
{
	//Apr�s PushOrder
}

void Hivemind::UpdateGraph(const STurnData& turnData)
{
	// TODO Dans un futur lointain
}

void Hivemind::InitNPCs(const SNPCInfo* npcInfoArray, const int nb)
{
	// TODO
}

void Hivemind::InitGraph(const STileInfo* tileInfoArray, const int tileArraySize, const SObjectInfo* objectInfoArray, const int objectArraySize)
{
	// TODO
}
