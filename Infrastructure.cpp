#include <iostream>
#include "GlobalValues.hpp"

#include "Infrastructure.hpp"


Infrastructure::Infrastructure(unsigned int setLevel, unsigned int setMaxLevel, double setGold, int setStock):
  level(setLevel),
  maxLevel(setMaxLevel),
  gold(setGold),
  inStock(setStock)
{
	infrastructureText.setFont(*getCustomFont()); 
	infrastructureText.setCharacterSize(16); 
	infrastructureText.setPosition(200, 200);
};

void Infrastructure::draw(double x, double y)
{
	drawText(getName(), x - 60, y);

	stringstream goldString;	
	goldString << "Gold: " << gold << "(-" << upkeep() << ")";
	drawText(goldString.str(), x, y);

	stringstream levelString;	
	levelString << "Level: " << level << "/" << maxLevel;
	drawText(levelString.str(), x, y + 20);

	drawText(strPlusX("Stock: ", inStock), x, y + 40);
	drawText(strPlusX("Sells for: ", wouldSellFor()), x + 170, y + 40);

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


Farm::Farm(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock):
	Infrastructure(setLevel, setMaxPotential, setGold, setGold)
{

}
string Farm::getName()
{
	return "Farm";
}

WoodMill::WoodMill(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock):
	Infrastructure(setLevel, setMaxPotential, setGold, setGold)
{

}
string WoodMill::getName()
{
	return "Woodmill";
}

Mine::Mine(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock):
	Infrastructure(setLevel, setMaxPotential, setGold, setGold)
{

}
string Mine::getName()
{
	return "Mine";
}