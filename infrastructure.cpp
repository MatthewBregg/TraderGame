#include <iostream>
#include "GlobalValues.hpp"

#include "Infrastructure.hpp"


Infrastructure::Infrastructure(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock):
  level(setLevel),
  maxPotential(setMaxPotential),
  gold(setGold),
  inStock(setStock)
{
	infrastructureText.setFont(*getCustomFont()); 
	infrastructureText.setCharacterSize(16); 
	infrastructureText.setPosition(200, 200);
};

void Infrastructure::draw(double x, double y)
{
	drawText(getName(), x - 80, y);
	drawText(strPlusX("Gold: ", gold), x, y);
	drawText(strPlusX("Upkeep: ", upkeep()), x + 170, y);
	drawText(strPlusX("Level: ", level), x, y + 20);
	drawText(strPlusX("Max level: ", maxPotential), x + 170, y + 20);
	drawText(strPlusX("Stock: ", inStock), x, y + 40);
	drawText(strPlusX("Sells for: ", wouldSellFor()), x + 170, y + 40);

}
void Infrastructure::refreshAfterTurn()
{
	if (gold >= upkeep())
	{
		gold -= upkeep();
	}
	else
	{
		level--;
	}
	inStock += level + 1;
}

double Infrastructure::wouldSellFor()
{
	return (upkeep() + gold + 1) / double(inStock);
}
double Infrastructure::upkeep()
{
	return level;
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