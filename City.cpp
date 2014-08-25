#include "GlobalValues.hpp"

#include "City.hpp"



 City::City(Resources r, int g):
	resources(r),
	gold(g),
	population(10000)
 {
 };

void City::draw(double x, double y)
{
	drawText(strPlusX("Population: ", population), x, y);
	drawText(strPlusX("Population change: ", getPopulationChange()), x + 170, y);
	drawText(strPlusX("Food in stock: ", resources.getFood()), x, y + 30);
	drawText(strPlusX("Food required: ", getPopulationFoodReq()), x + 170, y + 30);
}
void City::refreshAfterTurn()
{
	updatePopulation();
}

void City::updatePopulation()
{
	resources.subtractFood(getPopulationFoodReq());
	population *= getPopulationChange();
}


unsigned int City::getPopulationFoodReq()
{
	return ceil(double(population)/2000.0);
}
double City::getPopulationChange()
{
	if (resources.getFood() == 0)		// Nothing to eat.
	{
		return 0.7;	// Litte food, population plummets.
	}
	else if (resources.getFood() >= getPopulationFoodReq())
	{
		return 1.1;	// Lots of food, population increases.
	}
	else if (resources.getFood() >= getPopulationFoodReq() * 0.8)
	{
		return  1;	 // Stays the same.
	}
	else 
	{
		return 0.9;		// Litte food, population decreases.
	}
}