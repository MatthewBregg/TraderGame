#include <iostream>
#include "GlobalValues.h"
#include "Texture.h"

#include "Infrastructure.h"



Infrastructure::Infrastructure(unsigned int setLevel, unsigned int setMaxLevel, double setGold, int setStock, int xPos, int yPos):
level(setLevel),
maxLevel(setMaxLevel),
gold(setGold),
inStock(setStock),
buyFromButton(0, 0, 50, 20, "Buy", button1, 14)
{
	infrastructureText.setFont(getCustomFont()); 
	infrastructureText.setCharacterSize(16); 
	infrastructureText.setPosition(200, 200);
};

void Infrastructure::draw()
{

}

void Infrastructure::drawMenu(double x, double y)
{
	stringstream nameString;
	nameString << getName() << "(" << "Level: " << level << "/" << maxLevel << ")";

	drawText(nameString.str(), x + 60, y);

	stringstream goldString;
	goldString << "Gold: " << gold << "(-" << upkeep() << ")";
	drawText(goldString.str(), x + 20, y + 15);

	drawText(strPlusX("Stock: ", inStock), x + 20, y + 30);
	drawText(strPlusX("Sells for: ", wouldSellFor()), x + 20, y + 45);

	buyFromButton.setPos(x + 160, y + 43);
}

void Infrastructure::drawBuyingButton()
{
	buyFromButton.draw();
}

bool Infrastructure::isBuyingButtonClickedOn()
{
	return buyFromButton.isClickedOnRelative();
}

const double LEVEL_UPGRADE_COST = 6;
// Updates the infrastructure and returns the upkeep for that turn.
double Infrastructure::refreshAfterTurn()
{
	inStock += level + 1;

	double returnedUpkeep = upkeep();
	if (gold >= upkeep())
	{
		// Enough money, all is good.
		gold -= upkeep();
	}
	else  
	{
		// Bankrupt, drop a level and give all the remaining gold as upkeep.
		returnedUpkeep = gold;
		gold = 0;
		level--;
	}

	if ((gold >= LEVEL_UPGRADE_COST + upkeep() * 3) && level < maxLevel)
	{
		// Loads a money, upgrade a level.
		level++;
		returnedUpkeep += LEVEL_UPGRADE_COST;
		gold -= LEVEL_UPGRADE_COST;
	}

	return returnedUpkeep;
}

double Infrastructure::wouldSellFor()
{
	if (inStock <= 0)
	{
		return 1000000;
	}
	// inStock * 2 - eager to sell of excess stock.
	return (upkeep() + gold + 1) / double(inStock * 2); 
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