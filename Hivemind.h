#pragma once
#include "Globals.h"
#include "InitData.h"
#include "TurnData.h"

#include <list>
#include <vector>

class Hivemind
{
private:
	// TODO
	// std::vector<NPC*> _npcs{};
	// Graph _graph;

public:
	Hivemind() = default;
	~Hivemind() = default;

	void Init(const SInitData& _initData);
	void AStarSolution();
	void PushNextOrder(std::list<SOrder>& orders); // À voir...
	void StopConflictingNPCs(); // À voir...
	void UpdateGraph(const STurnData& turnData); // À voir...

private:
	void InitNPCs(const SNPCInfo* npcInfoArray, const int nb);
	void InitGraph(const STileInfo* tileInfoArray, const int tileArraySize,
				   const SObjectInfo* objectInfoArray = nullptr, const int objectArraySize = 0);
};