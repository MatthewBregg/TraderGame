#include <iostream>
#include "Texture.hpp"
#include "GlobalValues.hpp"


#include "Regions.hpp"


City* Region::selectedCity = nullptr;

Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName):
	texture(nullptr),
	city(cityName, Resources(40, 0, 0), 20, poses.at(0).x + 75, poses.at(0).y + 70),
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

	// To check if there are any bugs when exchanging gold.
	drawText(strPlusX("Total gold: ", city.getGold() + farm.getGold()), 150, 500);


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

double buyingPrice = 0;
double sellingPrice = 0;
void Region::updateAfterTurn()
{
	while (city.cityWouldAcceptDeal(farm.wouldSellFor())) 
	{
		city.acceptDeal(farm.wouldSellFor());
		farm.acceptDeal();
	}

	// Farm also returns the upkeep value to the city.
	// I don't like this, since each function is doing several things.
	city.refreshAfterTurn(
		farm.refreshAfterTurn()
		);

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
// 8  9 11 12 13 
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
	regions.push_back(Region(hexPos, elfFaction, grassLandsHex, "Rivendell"));
	hexPos.clear();

	hexPos.push_back(getHexPos(2));
	hexPos.push_back(getHexPos(6));
	hexPos.push_back(getHexPos(3));
	hexPos.push_back(getHexPos(7));
	regions.push_back(Region(hexPos, dwarfFaction, woodlandsHex, "Khazad-dum"));
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
	for (auto& i : regions)
	{
		i.drawMenu();
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
		// Some empty spot clicked, deselect the city.
		Region::selectedCity = nullptr;
	}
	return false;
}

void World::updateAfterTurn()
{
	for ( auto& i : regions)
    {
		i.updateAfterTurn();
    }
}

