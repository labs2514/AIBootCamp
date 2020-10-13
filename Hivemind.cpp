#include "Hivemind.h"

#include <algorithm>

void Hivemind::Init(const SInitData& _initData)
{
	InitGraph(_initData);
	InitNPCs(_initData.npcInfoArray, _initData.nbNPCs);
	AStarSolution();	// Ne devrait pas être fait dans Init à mon avis, Init devrait être utiliser pour initialiser, pas calculer
}

bool Hivemind::AStarSolution()
{
	bool solFound = true;
	if (_graph->getGoals().size() < _npcs.size())
	{
		return false;
	}

	for_each(begin(_npcs), end(_npcs), [&](auto& p)
	{
		NPC *npc = p.second;
		vector<STileCoord> path = _graph->getBestPath({npc->getPos()});
		if(path.empty())
		{
			solFound = false;
		}
		else
		{
			npc->setPath(path);
			_graph->reserveGoal(path.back());
		}
	});

	if(!solFound)
	{
		for_each(begin(_npcs), end(_npcs), [&](auto& p)
		{
			NPC *npc = p.second;
			_graph->returnGoal(npc->getPath().back());
			npc->clearPath(); // clear le path et reset le goal
		});	
	}
	
	return solFound;
}

void Hivemind::PushNextOrder(std::list<SOrder>& orders)
{
	// TODO Après AStar

	for_each(std::begin(_npcs), std::end(_npcs), [&](auto& p)
	{
		NPC* npc = p.second;

		orders.push_back(npc->getOrder());
	});
}

//void Hivemind::StopConflictingNPCs()
//{
//	//Après PushOrder
//}

void Hivemind::UpdateGraph(const STurnData& turnData)
{
	// TODO Dans un futur lointain
}

void Hivemind::InitGraph(const SInitData& _init)
{
	_graph = new Graph(_init);
}

void Hivemind::InitNPCs(const SNPCInfo* npcInfoArray, const int nb)
{
	// TODO
	// Pendant le parcours des npcs appeler _graph->setCellUser(cell du npc, uid du npc)

	std::for_each(npcInfoArray, npcInfoArray + nb, [&](const SNPCInfo& npcInfo)
	{
		_npcs.emplace(npcInfo.uid, new NPC(npcInfo.uid, STileCoord{npcInfo.q, npcInfo.r}));
		_graph->setCellUser(STileCoord{ npcInfo.q, npcInfo.r }, npcInfo.uid);
	});
}
