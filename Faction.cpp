#include "Texture.h"

#include "Faction.h"

array<Faction, TOTAL_FACTIONS> factions = { Faction("Elves"), Faction("Dwarves"), Faction("Demons") };


Faction::Faction(string setName):
name(setName),
soldiers(100)
{
	for (int i = 0; i < TOTAL_FACTIONS; ++i)
	{
		relations.push_back(1.0 - double(getRandomNumber(2000)) / 1000.0);  // At the start of the game, all relations are neutral.
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
				if (factions[row].relations[column] < - 0.4)
				{
					colorUsed = sf::Color::Red;
				}
				else if (factions[row].relations[column] > 0.4)
				{
					colorUsed = sf::Color::Green;
				}
				drawText(strPlusX("", factions[row].relations[column]),
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


Faction* getFaction(FactionEnum factionIndex)
{
	return &factions[factionIndex];
}
