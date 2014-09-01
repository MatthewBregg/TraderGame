#include "GlobalValues.h"


#include "Faction.h"

array<Faction, TOTAL_FACTIONS> factions = { Faction(), Faction(), Faction() };


Faction::Faction():
soldiers(100)
{

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
