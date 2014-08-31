﻿#include <iostream>
#include "Texture.h"
#include "GlobalValues.h"


#include "Regions.h"


Region* Region::selectedRegion = nullptr;

Resources Region::playerResources(5, 0, 0);
double Region::playerGold(10);

Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold):
	texture(nullptr),
	city(cityName, Resources(40, 0, 0), cityGold, poses.at(0).x + 75, poses.at(0).y + 70),
	farm(1, 6, 10, 0, 170, 120),
	woodmill(0, 0, 0, 0, 0, 0),
	mine(0, 0, 0, 0, 0, 0),
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

	menu.setPosition(500, 50);
	menu.setTexture(getTexture(randomBg));
	menu.setScale(290.0 / getTexture(randomBg).getSize().x, 400.0 / getTexture(randomBg).getSize().y);
};

void Region::draw()
{
	for (auto& hexSprite : hexagons)
	{	  
		window->draw(hexSprite);
	}

	city.draw();
	farm.draw();
	tradeCentre.draw();
	woodmill.draw();
	mine.draw();

	drawMenu();
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

void Region::drawMenu()
{
	if (selectedRegion == this)
	{
		window->draw(menu);
		city.drawMenu(menu.getPosition().x, menu.getPosition().y);
		farm.drawMenu(menu.getPosition().x, menu.getPosition().y + 110);
		woodmill.drawMenu(menu.getPosition().x, menu.getPosition().y + 175);
		mine.drawMenu(menu.getPosition().x, menu.getPosition().y + 240);
		if (tradeCentre.hasBeenBuilt())
		{
			// Draw the buttons that allow the player to sell/buy.
			city.drawSellingButton(menu.getPosition().x + 50, menu.getPosition().y + 25);
			farm.drawBuyingButton(menu.getPosition().x, menu.getPosition().y + 90);
			woodmill.drawBuyingButton(menu.getPosition().x, menu.getPosition().y + 155);
			mine.drawBuyingButton(menu.getPosition().x, menu.getPosition().y + 220);

			drawText(strPlusX("Player gold: ", playerGold), menu.getPosition().x + 20, menu.getPosition().y + 310);
			drawText(strPlusX("Player food: ", playerResources.get(foodResource)), menu.getPosition().x + 20, menu.getPosition().y + 330);
			drawText(strPlusX("Player wood: ", playerResources.get(woodResource)), menu.getPosition().x + 20, menu.getPosition().y + 345);
			drawText(strPlusX("Player steel: ", playerResources.get(steelResource)), menu.getPosition().x + 20, menu.getPosition().y + 360);
		}
	}
}

bool Region::handleMenuInput()
{
	if (city.isSellingButtonClickedOn())
	{
		if (playerResources.get(foodResource) > 0)
		{
			playerGold += city.getBuyingPrice();
			city.acceptDeal(city.getBuyingPrice());
			playerResources.change(foodResource, -1);
		}
		return true;
	}
	if (farm.isBuyingButtonClickedOn())
	{
		if (playerGold >= farm.wouldSellFor())
		{
			playerGold -= farm.wouldSellFor();
			playerResources.change(foodResource, 1);
			farm.acceptDeal();
		}
		return true;
	}

	if (woodmill.isBuyingButtonClickedOn())
	{
		if (playerGold >= woodmill.wouldSellFor())
		{
			playerGold -= woodmill.wouldSellFor();
			playerResources.change(woodResource, 1);
			woodmill.acceptDeal();
		}
		return true;
	}

	if (mine.isBuyingButtonClickedOn())
	{
		if (playerGold >= mine.wouldSellFor())
		{
			playerGold -= mine.wouldSellFor();
			playerResources.change(steelResource, 1);
			mine.acceptDeal();
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

World::World():
populationGraph("Population", 50, 400)
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
	regions.push_back(Region(hexPos, elfFaction, grassLandsHex, "Shire", 5));
	cityNames.push_back("Shire");
	hexPos.clear();

	populationGraph.initialise(
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
void World::drawMenu()
{
	double totalGold = Region::playerGold;
	for (auto& region : regions)
	{
		region.drawMenu();
		totalGold += region.city.getGold() + region.farm.getGold();
	}

	// To check if there are any bugs when exchanging gold.
	drawText(strPlusX("Total gold: ", totalGold), 350, 500);

	populationGraph.draw();
}
bool World::handleInput()
{
	if (Region::selectedRegion != nullptr)
	{
		if (Region::selectedRegion->handleMenuInput())
		{
			return true;
		}
	}
		
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

	for (int i = 0; i < regions.size(); ++i)
    {
		regions.at(i).updateAfterTurn();
		populationGraph.update(i, regions.at(i).city.getPopulation());
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
