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
	//std::vector<NPC*> _npcs{}; // faire une map<int, NPC*> plut�t ?
	Graph *_graph;

public:
	Hivemind() = default;
	~Hivemind() = default;

	void Init(const SInitData& _initData);
	bool AStarSolution(); // renvoyer un bool pour savoir si on a trouv� une solution ?
	void PushNextOrder(std::list<SOrder>& orders); // � voir...
	void StopConflictingNPCs(); // � voir...
	void UpdateGraph(const STurnData& turnData); // � voir...

private:
	void InitNPCs(const SNPCInfo* npcInfoArray, const int nb);
	void InitGraph(const SInitData& _init);
};