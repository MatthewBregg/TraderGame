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

	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		lowestPrice.push_back(0);
	}
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

	drawText(strPlusX("Food in stock: ", resources.get(foodResource)), x + 20, y + 70);
	drawText(strPlusX("Buys at max: ", getBuyingPrice(foodResource)), x + 20, y + 85);
	drawText(strPlusX("Buys from YOU at: ", lowestPrice.at(foodResource)), x + 20, y + 100);

	drawText(strPlusX("Wood in stock: ", resources.get(woodResource)), x + 20, y + 115);
	drawText(strPlusX("Buys at max: ", getBuyingPrice(woodResource)), x + 20, y + 130);
	drawText(strPlusX("Buys from YOU at: ", lowestPrice.at(woodResource)), x + 20, y + 145);

	drawText(strPlusX("Steel in stock: ", resources.get(steelResource)), x + 20, y + 160);
	drawText(strPlusX("Buys at max: ", getBuyingPrice(steelResource)), x + 20, y + 175);
	drawText(strPlusX("Buys from YOU at: ", lowestPrice.at(steelResource)), x + 20, y + 190);

	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		sellToButtons[i].setPos(x + 230, y + 98 + 45 * i);
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



    for ( int A = getFirstResourceEnum(); A != TOTAL_RESOURCES; ++A) //Slightly dangerous, relies on enums being contigious
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

// Set the lowest price the city can get. This will be used as the price 
// at which the city will buy from the player. Done here so it is only refreshed once.
// If city can get food at 0.4 at the start of the turn, player will have to 
// sell at that price for the whole turn. Otherwise, if player buys 1 food from 
// farm, the price would go up (as farm would no longer have as much food in stock).
// Thus the min price would increase, and player could make money just by buying
// things from infrastructures and selling right off to cities. 
void City::setNewLowestPrice(ResourceEnum resourceTraded, double newPrice)
{
	lowestPrice.at(resourceTraded) = newPrice;
}

// The price at which the city buys from infrastructures.
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
// The price at which the city buys from the player.
double City::getPlayerBuyingPrice(ResourceEnum resource)
{
	return lowestPrice.at(resource);
}

unsigned int City::getPopulationFoodReq()
{
	return ceil(double(population) / 2000.0);
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
