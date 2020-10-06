#pragma once
#include "Globals.h"
#include "InitData.h"
#include "TurnData.h"
#include "Graph.h"

#include <list>
#include <vector>


class Hivemind
{
private:
	// TODO
	//std::vector<NPC*> _npcs{}; // faire une map<int, NPC*> plutôt ?
	Graph *_graph;

public:
	Hivemind() = default;
	~Hivemind() = default;

	void Init(const SInitData& _initData);
	bool AStarSolution(); // renvoyer un bool pour savoir si on a trouvé une solution ?
	void PushNextOrder(std::list<SOrder>& orders); // À voir...
	void StopConflictingNPCs(); // À voir...
	void UpdateGraph(const STurnData& turnData); // À voir...

private:
	void InitNPCs(const SNPCInfo* npcInfoArray, const int nb);
	void InitGraph(const SInitData& _init);
};