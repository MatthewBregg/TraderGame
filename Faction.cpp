

#include "Faction.h"

array<Faction, TOTAL_FACTIONS> factions = { Faction("Elves"), Faction("Dwarves"), Faction("Demons") };


Faction::Faction(string setName):
name(setName),
soldiers(100)
{
	for (int i = 0; i < TOTAL_FACTIONS; ++i)
	{
		relations.push_back(0);  // At the start of the game, all relations are neutral.
	}
}

int Faction::getSoldiers()
{
	return soldiers;
}

void Faction::changeSolders(int byHowMuch)
{
	soldiers += byHowMuch;
	if (soldiers < 0)
	{
		soldiers = 0;
	}
}



Faction* getFaction(FactionEnum factionIndex)
{
	return &factions[factionIndex];
}
