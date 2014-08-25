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
	drawText(strPlusX("Food in stock: ", resources.getFood()), x, y + 25);
	drawText(strPlusX("Food required: ", getPopulationFoodReq()), x + 170, y + 25);
	drawText(strPlusX("Gold: ", gold), x, y + 50);
	drawText(strPlusX("Buys for: ", getBuyingPrice()), x + 170, y + 50);
}
void City::refreshAfterTurn(double upkeepFromInfrastructures)
{
	gold += upkeepFromInfrastructures;
	updatePopulation();
}


double City::getBuyingPrice()
{
	double buyingPrice = (gold + getPopulationFoodReq() + 1) / (resources.getFood() + 1);
	if (buyingPrice > gold)  // Can't buy more than you have. 
	{
		return gold;
	}
	return buyingPrice;
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

bool City::cityWouldAcceptDeal(double offeredPrice)
{
	// Can only accept the deal if the price is less than the one we would like,
	// as well as we have enough gold in the first place for the deal to occur.
	if (getBuyingPrice() > offeredPrice && gold > offeredPrice)
	{
		return true;
	}
	return false;
}
void City::acceptDeal(double price)
{
	gold -= price;
	resources.addFood(1);
}


void City::updatePopulation()
{
	resources.subtractFood(getPopulationFoodReq());
	population *= getPopulationChange();
}

