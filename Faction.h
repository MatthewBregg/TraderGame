#ifndef FACTION_H
#define FACTION_H

#include "GlobalValues.h"
#include "ClickableRectangle.h"

enum FactionEnum
{
  elfFaction,
  dwarfFaction,
  demonFaction,
  TOTAL_FACTIONS,
};

class Faction
{
public:
	Faction(string setName);

	int getSoldiers();
	void changeSolders(int byHowMuch);

	// Draws the relations between the factions as a table.
	static void drawRelations(int x, int y);
private:
	string name;
	int soldiers;
	// Relationships with other factions. -1 - worst, 1 - best. 
	vector<double> relations;

	static TexturedRectangle relationDisplayBg;
};
extern Faction* getFaction(FactionEnum factionIndex);

#endif /* FACTION_H */
