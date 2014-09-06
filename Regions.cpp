#include "Texture.h"
#include "GlobalValues.h"


#include "Regions.h"


Region* Region::selectedRegion = nullptr;

TexturedRectangle Region::playerResourceMenu(5, 5, 340, 40, genericBg);
TexturedRectangle Region::regionMenu(500, 10, 290.0, 470.0, genericBg);
Resources Region::playerResources(vector<unsigned int> {0, 0, 0});
double Region::playerGold(1);

Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold):
	texture(nullptr),
	city(cityName, Resources(vector<unsigned int> {40, 0, 0}), cityGold, poses.at(0).x + 75, poses.at(0).y + 70, setFaction),
	farm(1, 6, 10, 0, 170, 120),
	woodmill(0, 4, 0, 0, 0, 0),
	mine(0, 4, 0, 0, 0, 0),
	tradeCentre(poses.at(1).x + 75, poses.at(1).y + 70),
	currentOwner(setFaction),
	origOwner(setFaction)
{
	for (auto& pos : poses)
	{
		sf::Sprite temp;
		temp.setTexture(getTexture(hexTexture));
		temp.setPosition(pos);
		temp.setScale(DEFAULT_HEX_SIZE / getTexture(hexTexture).getSize().x,
					  DEFAULT_HEX_SIZE / getTexture(hexTexture).getSize().y);
		hexagons.push_back(temp);
	}

};

void Region::draw()
{
	for (auto& hexSprite : hexagons)
	{	  
		window->draw(hexSprite);
	}

	city.draw(playerResources); //By making this method call the greyer out, keeps more encapsulation and crap. 
	farm.draw();
	tradeCentre.draw();
	woodmill.draw();
	mine.draw();
}

bool Region::handleInput()
{
	if (city.isClickedOnRelative() || tradeCentre.isClickedOnRelative())
	{
		if (selectedRegion == this)  // Already selected.
		{
			selectedRegion = nullptr;  // So deselect.
		}
		else
		{
			selectedRegion = this;
		}
		return true;
	}

	return false;
}

void Region::drawPlayerResourceMenu()
{
	playerResourceMenu.drawBackground();

	drawSprite(20, 9, 32, 32, goldIcon);
	drawText(strPlusX("          ", playerGold),  20, 15);

	drawSprite(130, 9, 32, 32, foodIcon);
	drawText(strPlusX("          ", playerResources.get(foodResource)), 130, 15);

	drawSprite(200, 9, 32, 32, woodIcon);
	drawText(strPlusX("          ", playerResources.get(woodResource)), 200, 15);
	
	drawSprite(270, 9, 32, 32, steelIcon);
	drawText(strPlusX("          ", playerResources.get(steelResource)), 270, 15);
}

void Region::drawMenu()
{
	regionMenu.setPos(getWindowWidth() - 300, getWindowHeight() / 2 - 300);
	regionMenu.drawBackground();

	int menuX = regionMenu.getPos().x;
	int menuY = regionMenu.getPos().y;

	city.drawMenu(menuX, menuY - 10);
	farm.drawMenu(menuX, menuY + 200);
	woodmill.drawMenu(menuX, menuY + 265);
	mine.drawMenu(menuX, menuY + 330);
	if (tradeCentre.hasBeenBuilt())
	{
		greyoutBuyButtons();// Detemine what should be greyed out.
		// Draw the buttons that allow the player to sell/buy.
		city.drawSellingButtons();
		farm.drawBuyingButton();
		woodmill.drawBuyingButton();
		mine.drawBuyingButton();
	}
}

void Region::greyoutBuyButtons()
{
	if (playerGold >= farm.wouldSellFor())
	{
		farm.unsetBuyButtonGrey();
	}
	else
	{
		farm.setBuyButtonGrey();
	}
	if (playerGold >= woodmill.wouldSellFor())
	{
		woodmill.unsetBuyButtonGrey();
	}
	else
	{
		woodmill.setBuyButtonGrey();
	}
	if (playerGold >= mine.wouldSellFor())
	{
		mine.unsetBuyButtonGrey();
	}
	else
	{
		mine.setBuyButtonGrey();
	}
}
bool Region::handleMenuInput()
{
	if (regionMenu.isMouseHovering())
	{
		// Check if player wants to sell something to the city.
		for (int i = 0; i < TOTAL_RESOURCES; ++i)
		{
			ResourceEnum resource = static_cast<ResourceEnum>(i);

			if (city.isSellingButtonClickedOn(resource))
			{
				if (playerResources.get(resource) > 0)
				{
					playerGold += city.getPlayerBuyingPrice(resource);
					city.acceptDeal(resource, city.getPlayerBuyingPrice(resource));
					playerResources.change(resource, -1);
				}
			}
		}
		greyoutBuyButtons(); //No need to check twice if we can buy from, if we've greyed it out, the buttons can't be clicked.
		//Also don't have to worry about changing these values twice.
		if (farm.isBuyingButtonClickedOn())
		{
			if (!farm.isGreyed())
			{
				playerGold -= farm.wouldSellFor();
				playerResources.change(foodResource, 1);
				farm.acceptDeal();
			}
		}
		if (woodmill.isBuyingButtonClickedOn())
		{
			if (!woodmill.isGreyed())
			{
				playerGold -= woodmill.wouldSellFor();
				playerResources.change(woodResource, 1);
				woodmill.acceptDeal();
			}
		}
		if (mine.isBuyingButtonClickedOn())
		{
			if (!mine.isGreyed())
			{
				playerGold -= mine.wouldSellFor();
				playerResources.change(steelResource, 1);
				mine.acceptDeal();
			}
		}
		// As long as the mouse is over the menu, don't consider input for other things.
		return true;
	}
	return false;
}

void Region::updateAfterTurn()
{
	double farmUpkeep = farm.refreshAfterTurn() + woodmill.refreshAfterTurn() + mine.refreshAfterTurn();
	city.addGold(farmUpkeep);
	city.refreshAfterTurn();
	// Set the lowest price the city can get. This will be used as the price 
	// at which the city will buy from the player. Done here so it is only refreshed once.
	// If city can get food at 0.4 at the start of the turn, player will have to 
	// sell at that price for the whole turn. Otherwise, if player buys 1 food from 
	// farm, the price would go up (as farm would no longer have as much food in stock).
	// Thus the min price would increase, and player could make money just by buying
	// things from infrastructures and selling right off to cities. 
	city.setNewLowestPrice(foodResource, world.getMinSellingPrice(foodResource, this)->wouldSellFor());
	city.setNewLowestPrice(woodResource, world.getMinSellingPrice(woodResource, this)->wouldSellFor());
	city.setNewLowestPrice(steelResource, world.getMinSellingPrice(steelResource, this)->wouldSellFor());
}

void Region::setTexture(sf::Texture* tex)
{
	for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		(*it).setTexture(*tex); 
    }
}

// ----------- MAP

World world;

// Hexes are structured like this:
//  12 13 14 15 
// 8  9 10 11  
//  4  5  6  7  
// 0  1  2  3    
// This method, given an index, returns the world px position.
const int HEX_PER_ROW = 4;
sf::Vector2f getHexPos(int index)
{
	// ((index % 6) % 2) - ofset every second row. 
	return sf::Vector2f(
		DEFAULT_HEX_SIZE * 1.5 * (index % HEX_PER_ROW) + (DEFAULT_HEX_SIZE * 0.75) * ((index / HEX_PER_ROW) % 2),
		-DEFAULT_HEX_SIZE * 0.43 * (index / HEX_PER_ROW)
		);
}

World::World():
populationGraph("Population", 50, 375, true),
foodPriceGraph("Food prices", 350, 375, false)
{
	std::vector<sf::Vector2f> hexPos;
	vector <string> cityNames;

	hexPos.push_back(getHexPos(0));
	hexPos.push_back(getHexPos(4));
	hexPos.push_back(getHexPos(1));
	hexPos.push_back(getHexPos(5));
	regions.push_back(Region(hexPos, elfFaction, woodlandsHex, "Rivendell", 10));
	cityNames.push_back("Rivendell");
	hexPos.clear();

	hexPos.push_back(getHexPos(2));
	hexPos.push_back(getHexPos(6));
	hexPos.push_back(getHexPos(3));
	hexPos.push_back(getHexPos(7));
	regions.push_back(Region(hexPos, dwarfFaction, hillHex, "Khazad-dum", 40));
	cityNames.push_back("Khazad-dum");
	hexPos.clear();

	hexPos.push_back(getHexPos(8));
	hexPos.push_back(getHexPos(12));
	hexPos.push_back(getHexPos(9));
	hexPos.push_back(getHexPos(13));
	regions.push_back(Region(hexPos, demonFaction, grassLandsHex, "Shire", 5));
	cityNames.push_back("Shire");
	hexPos.clear();

	populationGraph.initialise(
		regions.size(), 
		vector < sf::Color > {sf::Color::Red, sf::Color::Green, sf::Color::Blue}, 
		cityNames
		);
	foodPriceGraph.initialise(
		regions.size(),
		vector < sf::Color > {sf::Color::Red, sf::Color::Green, sf::Color::Blue},
		cityNames
		);
}

void World::draw()
{
	for ( auto& i : regions)
	{
		i.draw();
	}
}
bool World::handleInput()
{
	for (auto& i : regions)
	{
		if (i.handleInput())
		{
			return true;
		}
	}
	if (leftClickPressed)
	{
		// Some empty spot clicked, deselect the city and trade centre.
		Region::selectedRegion = nullptr;
	}
	return false;
}
void World::drawMenu()
{
	if (Region::selectedRegion != nullptr)
	{
		Region::selectedRegion->drawMenu();
	}
	Region::drawPlayerResourceMenu();


	// To check if there are any bugs or rounding errors when exchanging gold.
	double totalGold = Region::playerGold;
	for (auto& region : regions)
	{
		totalGold += region.city.getGold() + region.farm.getGold() + region.woodmill.getGold() + region.mine.getGold();
	}
	drawText(strPlusX("Total gold: ", totalGold), getWindowWidth() / 2, getWindowHeight() - 50);

	populationGraph.draw();
	foodPriceGraph.draw();
	// Draws the relations between the factions as a table.
	Faction::drawRelations(50, 250);
}
bool World::handleMenuInput()
{
	if (Region::selectedRegion != nullptr)
	{
		if (Region::selectedRegion->handleMenuInput())
		{
			return true;
		}
	}
	return false;
}

// Returns true if any of the given elements is true.
bool canNewDealsOccur(const vector<bool>* aNewDealCanOccur)
{
	bool canNewDealsOccurReturn = false;
	for (int i = 0; i < aNewDealCanOccur->size(); i++)
	{
		// As long as there is some element that might be traded, a new deal can occur.
		if (aNewDealCanOccur->at(i))
		{
			canNewDealsOccurReturn = true;
		}
	}
	return canNewDealsOccurReturn;
}

void World::handleTrading()
{
	// Tries to make a deal between the city offering the most money, and
	// the infrastructure asking the smallest price. 
	// Checks if any particular resource can be traded. Needed as we start
	// trading starting with the most wanted resource. Even if noone might
	// afford it, there might be some other resources that can be traded.
	vector<bool> aNewDealCanOccur;	
	for (int i = 0; i < TOTAL_RESOURCES; ++i)	
	{	
		aNewDealCanOccur.push_back(true);
	}

	while (canNewDealsOccur(&aNewDealCanOccur))
	{
		// Find the resource that would be payed for the most (as long as a deal can occur for it).
		ResourceEnum mostWantedResource = getMostWantedResource(&aNewDealCanOccur);

		// Find the region with the city offering the most for that resource.
		Region* regionWithCityOfferingTheMost = getMaxBuyingPrice(mostWantedResource);
		if (regionWithCityOfferingTheMost != nullptr)
		{
			// Find the infrastructure that sells for the smallest price.
			Infrastructure* infrastructureAskingTheLeast = getMinSellingPrice(mostWantedResource, regionWithCityOfferingTheMost);
			if (infrastructureAskingTheLeast != nullptr &&
				regionWithCityOfferingTheMost->city.wouldAcceptDeal(mostWantedResource, infrastructureAskingTheLeast->wouldSellFor()))
			{
				// The buyer offers more than the seller asks for, a deal occurs.
				regionWithCityOfferingTheMost->city.acceptDeal(mostWantedResource, infrastructureAskingTheLeast->wouldSellFor());
				infrastructureAskingTheLeast->acceptDeal();
			}
			else
			{
				aNewDealCanOccur.at(mostWantedResource) = false;
			}
		}

		else
		{
			// The cheapest infrastructure is asking for more gold than the most expensive city
			// can offer. No other deals can occur FOR THIS PARTICULAR RESOURCE. Since
			// we start with the most expensive resource, there might be some other, cheaper
			// resources that we can trade.
			aNewDealCanOccur.at(mostWantedResource) = false;
		}
	}
}

void World::updateAfterTurn()
{
	handleTrading();

	for (int i = 0; i < regions.size(); ++i)
    {
		regions.at(i).updateAfterTurn();
		populationGraph.update(i, regions.at(i).city.getPopulation());
		foodPriceGraph.update(i, regions.at(i).farm.wouldSellFor());
    }
}

// ------------- Private

// Returns the resource that would be payed for the most. For example, city a pays
// (1, 5, 6) for each resource. City b pays (7, 3, 4). The most wanted resource is the 
// first one, as someone would pay 7 gold for it.
// Only elements for whom a new deal can occur are considered.
ResourceEnum World::getMostWantedResource(const vector<bool>* aNewDealCanOccur)
{
	ResourceEnum mostWantedResource = TOTAL_RESOURCES; // Initialise to an invalid index.
	// Initialise to some proper resource.
	for (int resource = 0; resource < TOTAL_RESOURCES; ++resource)
	{
		if (aNewDealCanOccur->at(resource))
		{
			mostWantedResource = static_cast<ResourceEnum>(resource);
		}
	}

	double maxBuyingPrice = 0;
	for (auto& region : regions)
	{
		for (int resource = 0; resource < TOTAL_RESOURCES; ++resource)
		{
			if (aNewDealCanOccur->at(resource))
			{
				ResourceEnum resourceIndex = static_cast<ResourceEnum>(resource);
				double citiesBuyingPrice = region.city.getBuyingPrice(resourceIndex);
				if (maxBuyingPrice < citiesBuyingPrice)
				{
					maxBuyingPrice = citiesBuyingPrice;
					mostWantedResource = resourceIndex;
				}
			}
		}
	}
	return mostWantedResource;
}

// Returns the region with the city offering the largest price for 1 unit of some resource.
Region* World::getMaxBuyingPrice(ResourceEnum resource)
{
	Region* regionWithTheCityOfferingTheMost = nullptr;
	double maxBuyingPrice = 0;
	for (auto& region : regions)
	{
		double citiesBuyingPrice = region.city.getBuyingPrice(resource);
		if (maxBuyingPrice < citiesBuyingPrice)
		{
			maxBuyingPrice = citiesBuyingPrice;
			regionWithTheCityOfferingTheMost = &region;
		}
	}
	return regionWithTheCityOfferingTheMost;
}

// Returns the infrastructure asking the smallest price for the given resource.
// The startingRegion is where the city looking the deal is at. Needed since some regions might not
// be able to trade with infrastructures from other regions.
Infrastructure* World::getMinSellingPrice(ResourceEnum resource, Region* startingRegion)
{
	Infrastructure* infrastructureAskingTheLeast = nullptr;
	double minSellingPrice = 100000000;

	if (resource == foodResource)
	{
		double farmWouldSellFor = startingRegion->farm.wouldSellFor();
		if (minSellingPrice > farmWouldSellFor)
		{
			minSellingPrice = startingRegion->farm.wouldSellFor();
			infrastructureAskingTheLeast = &startingRegion->farm;
		}
	}
	else if (resource == woodResource)
	{
		double woodmillWouldSellFor = startingRegion->woodmill.wouldSellFor();
		if (minSellingPrice > woodmillWouldSellFor)
		{
			minSellingPrice = startingRegion->woodmill.wouldSellFor();
			infrastructureAskingTheLeast = &startingRegion->woodmill;
		}
	}
	else if (resource == steelResource)
	{
		double mineWouldSellFor = startingRegion->mine.wouldSellFor();
		if (minSellingPrice > mineWouldSellFor)
		{
			minSellingPrice = startingRegion->mine.wouldSellFor();
			infrastructureAskingTheLeast = &startingRegion->mine;
		}
	}
	else
	{
		assert(0 && "Not existing resource buying price requested.");
	}
	/*
	for (auto& region : regions)
	{
		if (resource == foodResource)
		{
			double farmWouldSellFor = region.farm.wouldSellFor();
			if (minSellingPrice > farmWouldSellFor)
			{
				minSellingPrice = region.farm.wouldSellFor();
				infrastructureAskingTheLeast = &region.farm;
			}
		}
		else if (resource == woodResource)
		{
			double woodmillWouldSellFor = region.woodmill.wouldSellFor();
			if (minSellingPrice > woodmillWouldSellFor)
			{
				minSellingPrice = region.woodmill.wouldSellFor();
				infrastructureAskingTheLeast = &region.woodmill;
			}
		}
		else if (resource == steelResource)
		{
			double mineWouldSellFor = region.mine.wouldSellFor();
			if (minSellingPrice > mineWouldSellFor)
			{
				minSellingPrice = region.mine.wouldSellFor();
				infrastructureAskingTheLeast = &region.mine;
			}
		}
		else
		{
			assert(0 && "Not existing resource buying price requested.");
		}
	}*/
	return infrastructureAskingTheLeast;
}
