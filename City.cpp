#include "GlobalValues.hpp"

#include "City.hpp"



 City::City(string setName, Resources r, int g):
	name(setName),
	resources(r),
	gold(g),
	population(10000)
 {
 };

void City::draw(double x, double y)
{
	drawText(name, x - 60, y);

	stringstream popString;	
	popString << "Population: " << population << "(*" << getPopulationChange() << ")";
	drawText(popString.str(), x, y);

	stringstream foodStockString;	
	foodStockString << "Food in stock: " << resources.getFood() << "(-" << getPopulationFoodReq() << ")";
	drawText(foodStockString.str(), x, y + 25);

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
	double buyingPrice = (gold + getPopulationFoodReq() + 1) / (resources.getFood() + 2);
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

double City::getGold()
{
	return gold;
}

// ------------------------------ Private

void City::updatePopulation()
{
	resources.subtractFood(getPopulationFoodReq());
	population *= getPopulationChange();
}