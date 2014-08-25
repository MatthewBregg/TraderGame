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
	stringstream infrastructureName;	infrastructureName << getName();
	infrastructureText.setString(infrastructureName.str());
	infrastructureText.setPosition(x, y);
	window->draw(infrastructureText);

	stringstream infrastructureUpkeep;	infrastructureUpkeep << "Upkeep: " << upkeep();
	infrastructureText.setString(infrastructureUpkeep.str());
	infrastructureText.setPosition(x + 170, y);
	window->draw(infrastructureText);


}
void Infrastructure::refreshAfterTurn()
{

}

double Infrastructure::upkeep()
{
	return level;
}

Farm::Farm():
	Infrastructure(0, 0, 0, 0)
{

}
string Farm::getName()
{
	return "Farm";
}

WoodMill::WoodMill():
	Infrastructure(0, 0, 0, 0)
{

}
string WoodMill::getName()
{
	return "Woodmill";
}

Mine::Mine():
	Infrastructure(0, 0, 0, 0)
{

}
string Mine::getName()
{
	return "Mine";
}