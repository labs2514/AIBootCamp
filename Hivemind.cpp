#include "Hivemind.h"

void Hivemind::Init(const SInitData& _initData)
{
	InitGraph(_initData);
	InitNPCs(_initData.npcInfoArray, _initData.nbNPCs);
	AStarSolution();
}

bool Hivemind::AStarSolution()
{
	bool solFound = true;
	/*if (_graph->getGoals().size() < _npcs.size())
	{
		return false;
	}
	for_each(begin(_npcs), end(_npcs), [&](auto& p)
	{
		NPC *npc = p.second;
		vector<STileCoord> path = _graph->getBestPath({npc->q, npc->r});
		if(path.empty())
		{
			solFound = false;
			break;
		} else
		{
			npc->setPath(path);
			npc->setGoal(path.back());
			_graph->reserveGoal(path.back());
		}
	});

	if(!solFound)
	{
		for_each(begin(_npcs), end(_npcs), [&](auto& p)
		{
			NPC *npc = p.second;
			_graph->returnGoal(npc->getGoal());
			npc->clearPath(); // clear le path et reset le goal
		});	
	}
	
	return solFound;*/
}

void Hivemind::PushNextOrder(std::list<SOrder>& orders)
{
	// TODO Après AStar
}

void Hivemind::StopConflictingNPCs()
{
	//Après PushOrder
}

void Hivemind::UpdateGraph(const STurnData& turnData)
{
	// TODO Dans un futur lointain
}

void Hivemind::InitNPCs(const SNPCInfo* npcInfoArray, const int nb)
{
	// TODO
	// Pendant le parcours des npcs appeler _graph->setCellUser(cell du npc, uid du npc)
}

void Hivemind::InitGraph(const SInitData& _init)
{
	_graph = new Graph(_init);
}
