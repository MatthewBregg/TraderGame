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

	static void initRelations();
	static Faction* get(FactionEnum factionIndex);
private:
	string name;
	int soldiers;
	// Relationships between factions. -1 - worst, 1 - best. 
	// A TOTAL_FACTIONS x TOTAL_FACTIONS table of relations.
	// It should be symetrical diagonally.
	static vector<vector<double>> relations;

	static TexturedRectangle relationDisplayBg;

};

#endif /* FACTION_H */
