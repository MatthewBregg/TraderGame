#include <iostream>
#include "GlobalValues.hpp"

#include "Infrastructure.hpp"


Infrastructure::Infrastructure(unsigned int setLevel, unsigned int setMaxLevel, double setGold, int setStock, int xPos, int yPos):
  level(setLevel),
  maxLevel(setMaxLevel),
  gold(setGold),
  inStock(setStock)
{
	infrastructureText.setFont(*getCustomFont()); 
	infrastructureText.setCharacterSize(16); 
	infrastructureText.setPosition(200, 200);
};

void Infrastructure::draw()
{

}
void Infrastructure::drawMenu(double x, double y)
{
	drawText(getName(), x + 60, y);

	stringstream goldString;
	goldString << "Gold: " << gold << "(-" << upkeep() << ")";
	drawText(goldString.str(), x + 20, y + 15);

	stringstream levelString;
	levelString << "Level: " << level << "/" << maxLevel;
	drawText(levelString.str(), x + 20, y + 30);

	drawText(strPlusX("Stock: ", inStock), x + 20, y + 45);
	drawText(strPlusX("Sells for: ", wouldSellFor()), x + 20, y + 60);

}

// Returns the upkeep for that turn.
double Infrastructure::refreshAfterTurn()
{
	inStock += level + 1;

	double returnedUpkeep = 0;
	if ((gold >= 5 + upkeep()*2) && level < maxLevel)
	{
		level++;
		returnedUpkeep += 4;  // Upgrade a level.
		returnedUpkeep += upkeep(); 
		gold -= 4;
		gold -= upkeep(); 
	}
	else if (gold >= upkeep())
	{
		gold -= upkeep(); 
		returnedUpkeep += upkeep(); 
	}
	else
	{
		returnedUpkeep += gold;
		gold = 0;
		level--;
	}

	return returnedUpkeep;
}

double Infrastructure::wouldSellFor()
{
	if (inStock <= 0)
	{
		return 100000;
	}
	return (upkeep() + gold + 1) / double(inStock);
}
double Infrastructure::upkeep()
{
	return level;
}

void Infrastructure::acceptDeal()
{
	gold += wouldSellFor();
	inStock--;
}
double Infrastructure::getGold()
{
	return gold;
}


Farm::Farm(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos) :
	Infrastructure(setLevel, setMaxPotential, setGold, setGold, xPos, yPos)
{

}
string Farm::getName()
{
	return "Farm";
}

WoodMill::WoodMill(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos) :
	Infrastructure(setLevel, setMaxPotential, setGold, setGold, xPos, yPos)
{

}
string WoodMill::getName()
{
	return "Woodmill";
}

Mine::Mine(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos) :
	Infrastructure(setLevel, setMaxPotential, setGold, setGold, xPos, yPos)
{

}
string Mine::getName()
{
	return "Mine";
}