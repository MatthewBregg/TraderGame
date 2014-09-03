#include "GlobalValues.h"
#include "Texture.h"

#include "City.h"

const double CITY_SIZE = 100;

City::City(string setName, Resources r, int g, int xPos, int yPos, FactionEnum setFaction):
	ClickableRectangle(xPos, yPos, CITY_SIZE, CITY_SIZE),
	name(setName),
	resources(r),
	gold(g),
	population(10000),
	factionIndex(setFaction),
	sellToButtons({ ButtonSfml(0, 0, 50, 20, "Sell", button1, 14), ButtonSfml(0, 0, 50, 20, "Sell", button1, 14), ButtonSfml(0, 0, 50, 20, "Sell", button1, 14) })
 {

	citySprite.setPosition(xPos, yPos);
	citySprite.setTexture(getTexture(randomCityTexture));
	citySprite.setScale(CITY_SIZE / getTexture(randomCityTexture).getSize().x, CITY_SIZE / getTexture(randomCityTexture).getSize().y);
 };

void City::draw()
{
	window->draw(citySprite);
}

void City::draw(const Resources player)
{
	window->draw(citySprite);
	greyOutSellingButtons(player);
}
void City::drawMenu(double x, double y)
{
	drawText(name, x + 60, y + 20);

	stringstream popString;
	popString << "Population: " << population << "(*" << getPopulationChange() << ")";
	drawText(popString.str(), x + 20, y + 40);

	drawText(strPlusX("", getFaction(factionIndex)->getSoldiers()), x + 220, y + 40);

	drawText(strPlusX("Gold: ", gold), x + 20, y + 55);

	stringstream foodStockString;
	foodStockString << "Food in stock: " << resources.get(foodResource) << "(-" << getPopulationFoodReq() << ")";
	drawText(foodStockString.str(), x + 20, y + 70);
	drawText(strPlusX("Buys food for: ", getBuyingPrice(foodResource)), x + 20, y + 85);

	stringstream woodStockString;
	woodStockString << "Wood in stock: " << resources.get(woodResource);
	drawText(woodStockString.str(), x + 20, y + 100);
	drawText(strPlusX("Buys wood for: ", getBuyingPrice(woodResource)), x + 20, y + 115);

	stringstream steelStockString;
	steelStockString << "Steel in stock: " << resources.get(steelResource);
	drawText(steelStockString.str(), x + 20, y + 130);
	drawText(strPlusX("Buys steel for: ", getBuyingPrice(steelResource)), x + 20, y + 145);

	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		sellToButtons[i].setPos(x + 230, y + 80 + 30 * i);
	}
}

void City::drawSellingButtons()
{

	for (auto& button : sellToButtons)
	{
		button.draw();
	}
}

void City::greyOutSellingButtons(const Resources& player)
{



    for ( int A = getFirstResourceEnum(); A != TOTAL_RESOURCES; ++A)
    	{
    	    if (player.get(A) == 0)
    		{
    		    sellToButtons[A].setGrey();
    		}
    	    else
    		{
    		    sellToButtons[A].unsetGrey();
    		}
    	}

 
}
bool City::isSellingButtonClickedOn(ResourceEnum resource)
{
	return sellToButtons[resource].isClickedOn();
}

void City::refreshAfterTurn()
{
	updatePopulation();
	updateSolders();
}

double City::getBuyingPrice(ResourceEnum resource)
{
	if (resource == foodResource)
	{
		return foodBuyingPrice();
	}
	else if (resource == woodResource)
	{
		return woodBuyingPrice();
	}
	else if (resource == steelResource)
	{
		return steelBuyingPrice();
	}
	else
	{
		assert(0 && "Not existing resource buying price requested.");
	}
	return 0;
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
		(double(resources.get(foodResource)) / double(getPopulationFoodReq())) * POPULATION_GROWTH_DIFF;
	if (populationChange > MAX_POPULATION_GROWTH)
	{
		populationChange = MAX_POPULATION_GROWTH;
	}
	return populationChange;
}

bool City::wouldAcceptDeal(ResourceEnum resourceTraded, double offeredPrice)
{
	// Can only accept the deal if the price is less than the one we would like,
	// as well as we have enough gold in the first place for the deal to occur.
	if (getBuyingPrice(resourceTraded) >= offeredPrice && gold >= offeredPrice)
	{
		return true;
	}
	return false;
}

void City::acceptDeal(ResourceEnum resourceTraded, double price)
{
	gold -= price;
	resources.change(resourceTraded, 1);
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
	resources.change(foodResource, -getPopulationFoodReq());
	population *= getPopulationChange();
}

// How many soldiers can be created using 1 wood and 1 steel.
const int SOLDIERS_CREATED = 20;

// Creates soldiers if there is enough wood and steel (and population).
void City::updateSolders()
{
	if (resources.get(woodResource) >= 1 && resources.get(steelResource) >= 1 && population >= 1000)
	{
		population -= SOLDIERS_CREATED;
		resources.change(woodResource, -1);
		resources.change(steelResource, -1);
		
		getFaction(factionIndex)->changeSolders(SOLDIERS_CREATED);
	}
}

double City::foodBuyingPrice()
{
	double buyingPrice = (gold + getPopulationFoodReq() + 1) / (sqrt(resources.get(foodResource)) + 2);
	if (buyingPrice > gold)  // Can't buy more than you have. 
	{
		return gold;
	}
	return buyingPrice;
}

// How many people from the population are required to be solders.
const double REQUIRED_NO_SOLDIERS = 0.1;
double City::woodBuyingPrice()
{
	double missingSoldiers = REQUIRED_NO_SOLDIERS * population - getFaction(factionIndex)->getSoldiers();
	if (missingSoldiers <= 0)
	{
		missingSoldiers = 0;
	}

	double buyingPrice = (gold * (missingSoldiers / double(population))) / (resources.get(woodResource) + 2);
	if (buyingPrice > gold)  // Can't buy more than you have. 
	{
		return gold;
	}
	return buyingPrice;
}

double City::steelBuyingPrice()
{
	double missingSoldiers = REQUIRED_NO_SOLDIERS * population - getFaction(factionIndex)->getSoldiers();
	if (missingSoldiers <= 0)
	{
		missingSoldiers = 0;
	}

	double buyingPrice = (gold * (missingSoldiers / double(population))) / (resources.get(steelResource) + 2);
	if (buyingPrice > gold)  // Can't buy more than you have. 
	{
		return gold;
	}
	return buyingPrice;
}
