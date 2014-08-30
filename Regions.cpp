#include <iostream>
#include "Texture.h"
#include "GlobalValues.h"


#include "Regions.h"


City* Region::selectedCity = nullptr;

Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold):
	texture(nullptr),
	city(cityName, Resources(40, 0, 0), cityGold, poses.at(0).x + 75, poses.at(0).y + 70),
	farm(1, 6, 10, 0, 170, 120),
	mill(0, 0, 0, 0, 0, 0),
	mine(0, 0, 0, 0, 0, 0),
	tradeCentre(),
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

	menu.setPosition(500, 80);
	menu.setTexture(getTexture(buttonTexture1));
	menu.setScale(290.0 / getTexture(buttonTexture1).getSize().x, 350.0 / getTexture(buttonTexture1).getSize().y);
};

void Region::draw()
{
	for (auto& hexSprite : hexagons)
	{	  
		window->draw(hexSprite);
	}

	city.draw();
	farm.draw();
	//mill.draw(400, 210);
	//mine.draw(400, 260);

	drawMenu();
}
void Region::drawMenu()
{
	if (selectedCity == &city)
	{
		window->draw(menu);
		city.drawMenu(menu.getPosition().x, menu.getPosition().y);
		farm.drawMenu(menu.getPosition().x, menu.getPosition().y + 150);
	}
}

bool Region::handleInput()
{
	if (city.isClickedOn())
	{
		if (selectedCity == &city)  // Already selected.
		{
			selectedCity = nullptr;  // So deselect.
		}
		else
		{
			selectedCity = &city;
		}
		return true;
	}
	return false;
}

void Region::updateAfterTurn()
{
	double farmUpkeep = farm.refreshAfterTurn();
	city.addGold(farmUpkeep);
	city.refreshAfterTurn();

	//mill.refreshAfterTurn();
	//mine.refreshAfterTurn();
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

World::World() 
{
	std::vector<sf::Vector2f> hexPos;

	hexPos.push_back(getHexPos(0));
	hexPos.push_back(getHexPos(4));
	hexPos.push_back(getHexPos(1));
	hexPos.push_back(getHexPos(5));
	regions.push_back(Region(hexPos, elfFaction, woodlandsHex, "Rivendell", 10));
	hexPos.clear();

	hexPos.push_back(getHexPos(2));
	hexPos.push_back(getHexPos(6));
	hexPos.push_back(getHexPos(3));
	hexPos.push_back(getHexPos(7));
	regions.push_back(Region(hexPos, dwarfFaction, hillHex, "Khazad-dum", 40));
	hexPos.clear();

	hexPos.push_back(getHexPos(8));
	hexPos.push_back(getHexPos(12));
	hexPos.push_back(getHexPos(9));
	hexPos.push_back(getHexPos(13));
	regions.push_back(Region(hexPos, elfFaction, grassLandsHex, "Shire", 5));
	hexPos.clear();
}

void World::draw()
{
	for ( auto& i : regions)
	{
		i.draw();
	}
}
void World::drawMenu()
{
	double totalGold = 0;
	for (auto& region : regions)
	{
		region.drawMenu();
		totalGold += region.city.getGold() + region.farm.getGold();
	}

	// To check if there are any bugs when exchanging gold.
	drawText(strPlusX("Total gold: ", totalGold), 150, 500);

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
		// Some empty spot clicked, deselect the city.
		Region::selectedCity = nullptr;
	}
	return false;
}


void World::handleTrading()
{
	// Tries to make a deal between the city offering the most money, and
	// the infrastructure asking the smallest price. 

	bool aNewDealCanOccur = true;
	while (aNewDealCanOccur)
	{
		// Find the city offering the most for food.
		City* cityOfferingTheMost = getMaxBuyingPrice();
		// Find the farm that sells for the smallest price.
		Farm* farmAskingTheLeast = getMinSellingPrice();

		if (cityOfferingTheMost != nullptr && 
			farmAskingTheLeast != nullptr && 
			cityOfferingTheMost->cityWouldAcceptDeal(farmAskingTheLeast->wouldSellFor()))
		{
			// The buyer offers more than the seller asks for, a deal occurs.
			cityOfferingTheMost->acceptDeal(farmAskingTheLeast->wouldSellFor());
			farmAskingTheLeast->acceptDeal();
		}
		else
		{
			// The cheapest farm is asking for more gold than the most expensive city
			// can offer. No other deals can occur.
			aNewDealCanOccur = false;
		}
	}
}

void World::updateAfterTurn()
{
	handleTrading();

	for ( auto& region : regions)
    {
		region.updateAfterTurn();
    }
}

// ------------- Private

// Returns the city offering the largest price for 1 unit of food.
City* World::getMaxBuyingPrice()
{
	City* cityOfferingTheMost = nullptr;
	double maxBuyingPrice = 0;
	for (auto& region : regions)
	{
		double citiesBuyingPrice = region.city.getBuyingPrice();
		if (maxBuyingPrice < citiesBuyingPrice)
		{
			maxBuyingPrice = region.city.getBuyingPrice();
			cityOfferingTheMost = &region.city;
		}
	}
	return cityOfferingTheMost;
}

// Returns the farm asking for the smallest price for 1 unit of food. 
Farm* World::getMinSellingPrice()
{
	Farm* farmAskingTheLeast = nullptr;
	double minSellingPrice = 100000000;
	for (auto& region : regions)
	{
		double farmWouldSellFor = region.farm.wouldSellFor();
		if (minSellingPrice > farmWouldSellFor)
		{
			minSellingPrice = region.farm.wouldSellFor();
			farmAskingTheLeast = &region.farm;
		}
	}
	return farmAskingTheLeast;
}