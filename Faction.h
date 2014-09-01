#ifndef FACTION_H
#define FACTION_H


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
	Faction();

	int getSoldiers();
	void changeSolders(int byHowMuch);
private:
	int soldiers;

};
extern Faction* getFaction(FactionEnum factionIndex);

#endif /* FACTION_H */
