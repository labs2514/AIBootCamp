#pragma once
#include "Globals.h"
#include "InitData.h"
#include "TurnData.h"
#include "Graph.h"
#include "NPC.h"

#include <list>
#include <vector>


class Hivemind
{
private:
	Graph *_graph = nullptr;
	std::map<int, NPC*> _npcs;

public:
	Hivemind() = default;
	~Hivemind() = default;

	void Init(const SInitData& _initData);
	bool AStarSolution(); // renvoyer un bool pour savoir si on a trouvé une solution ?
	void PushNextOrder(std::list<SOrder>& orders); // À voir...
	// void StopConflictingNPCs(); // À voir...
	void UpdateGraph(const STurnData& turnData); // À voir...

private:
	void InitGraph(const SInitData& _init);
	void InitNPCs(const SNPCInfo* npcInfoArray, const int nb);
};