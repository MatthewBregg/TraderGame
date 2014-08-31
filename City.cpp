#include "GlobalValues.h"
#include "Texture.h"

#include "City.h"

const double CITY_SIZE = 100;

City::City(string setName, Resources r, int g, int xPos, int yPos):
	ClickableRectangle(xPos, yPos, CITY_SIZE, CITY_SIZE),
	name(setName),
	resources(r),
	gold(g),
	population(10000)
 {
	citySprite.setPosition(xPos, yPos);
	citySprite.setTexture(getTexture(randomCityTexture));
	citySprite.setScale(CITY_SIZE / getTexture(randomCityTexture).getSize().x, CITY_SIZE / getTexture(randomCityTexture).getSize().y);

 };

void City::draw()
{
	window->draw(citySprite);
}
void City::drawMenu(double x, double y)
{
	drawText(name, x + 60, y + 20);

	stringstream popString;
	popString << "Population: " << population << "(*" << getPopulationChange() << ")";
	drawText(popString.str(), x + 20, y + 40);

	stringstream foodStockString;
	foodStockString << "Food in stock: " << resources.getFood() << "(-" << getPopulationFoodReq() << ")";
	drawText(foodStockString.str(), x + 20, y + 55);

	drawText(strPlusX("Gold: ", gold), x + 20, y + 70);
	drawText(strPlusX("Buys food for: ", getBuyingPrice()), x + 20, y + 85);
}

void City::refreshAfterTurn()
{
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

const double MIN_POPULATION_GROWTH = 0.7;
const double MAX_POPULATION_GROWTH = 1.1;
// How much the population growth can be affected by food.
const double POPULATION_GROWTH_DIFF = MAX_POPULATION_GROWTH - MIN_POPULATION_GROWTH;
double City::getPopulationChange()
{
	double populationChange = MIN_POPULATION_GROWTH + 
		(double(resources.getFood()) / double(getPopulationFoodReq())) * POPULATION_GROWTH_DIFF;
	if (populationChange > MAX_POPULATION_GROWTH)
	{
		populationChange = MAX_POPULATION_GROWTH;
	}
	return populationChange;
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
void City::addGold(double howMuch)
{
	gold += howMuch;
}

unsigned int City::getPopulation()
{
	return population;
}

// ------------------------------ Private

void City::updatePopulation()
{
	resources.subtractFood(getPopulationFoodReq());
	population *= getPopulationChange();
}
