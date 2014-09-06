#include "Texture.h"

#include "Faction.h"

array<Faction, TOTAL_FACTIONS> factions = { Faction("Elves"), Faction("Dwarves"), Faction("Demons") };
// Relationships between factions. -1 - worst, 1 - best. 
// A TOTAL_FACTIONS x TOTAL_FACTIONS table of relations.
// It should be symetrical diagonally.
vector<vector<double>> Faction::relations;

Faction::Faction(string setName):
name(setName),
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


const int DIST_BETWEEN_ROWS = 20;
const int DIST_BETWEEN_COLUMNS = 65;
const int X_OFFSET = 8;
const int Y_OFFSET = 4;
// Temp as relations should go into another menu (the journal)
const double TEMP_WIDTH = 270;
const double TEMP_HEIGHT = 100;

TexturedRectangle Faction::relationDisplayBg(0, 0, TEMP_WIDTH, TEMP_HEIGHT, genericBg);

// Draws the relations between the factions as a table.
void Faction::drawRelations(int x, int y)
{
	relationDisplayBg.setPos(x, y);
	relationDisplayBg.drawBackground();

	for (int row = 0; row < factions.size(); ++row)
	{
		drawText(factions[row].name, x + X_OFFSET, y + Y_OFFSET + DIST_BETWEEN_ROWS * (row + 1));
		drawText(factions[row].name, x + X_OFFSET + DIST_BETWEEN_COLUMNS * (row + 1), y + Y_OFFSET);

		for (int column = 0; column < factions.size(); ++column)
		{
			if (row != column)
			{
				sf::Color colorUsed = sf::Color::Black;
				if (relations.at(row).at(column) < -0.4)
				{
					colorUsed = sf::Color::Red;
				}
				else if (relations.at(row).at(column) > 0.4)
				{
					colorUsed = sf::Color::Green;
				}
				drawText(strPlusX("", relations.at(row).at(column)),
								  x + X_OFFSET + DIST_BETWEEN_COLUMNS * (column + 1),
								  y + Y_OFFSET + DIST_BETWEEN_ROWS * (row + 1),
								  14, 
								  colorUsed);
			}
			else // Dont draw Dwarf to Dwarf relations, as they have no effect.
			{
				drawText("X", x + X_OFFSET + DIST_BETWEEN_COLUMNS * (column + 1), y + Y_OFFSET + DIST_BETWEEN_ROWS * (row + 1));
			}
		}
	}
}

void Faction::initRelations()
{
	static bool inited = false;
	if (!inited)
	{
		// Relationships between factions. -1 - worst, 1 - best. 
		for (int i = 0; i < TOTAL_FACTIONS; ++i)
		{
			vector<double> relationVector;
			relations.push_back(relationVector);
			for (int f = 0; f < TOTAL_FACTIONS; ++f)
			{
				// At the start of the game, randomly init factions.
				relations.at(i).push_back(1.0 - double(getRandomNumber(2000)) / 1000.0);
			}
		}
		inited = true;

		for (int i = 0; i < TOTAL_FACTIONS; ++i)
		{
			for (int f = 0; f < TOTAL_FACTIONS; ++f)
			{
				// Make the relations symetrical diagonally.
				relations.at(i).at(f) = relations.at(f).at(i);
			}
		}
	}
}


Faction* Faction::get(FactionEnum factionIndex)
{
	return &factions[factionIndex];
}
