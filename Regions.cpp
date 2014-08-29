#include <iostream>
#include "Texture.hpp"
#include "GlobalValues.hpp"


#include "Regions.hpp"


City* Region::selectedCity = nullptr;

Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture):
	texture(nullptr),
	city("Bronx", Resources(40, 0, 0), 20, 170, 120),
	farm(1, 6, 10, 0, 170, 120),
	mill(0, 0, 0, 0, 0, 0),
	mine(0, 0, 0, 0, 0, 0),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)

{
	for (std::vector<sf::Vector2f>::iterator it = poses.begin(); it != poses.end(); ++it)
	{
		sf::Sprite temp;
		temp.setTexture(getTexture(hexTexture));
		temp.setPosition(*it);
		hexagons.push_back(temp);
	}

	menu.setPosition(500, 80);
	menu.setTexture(getTexture(buttonTexture1));
	menu.setScale(290.0 / getTexture(buttonTexture1).getSize().x, 350.0 / getTexture(buttonTexture1).getSize().y);
};

void Region::draw()
{
  for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		window->draw(*it);
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

void Map::draw()
{

	for ( auto& i : regions)
	{
		i.draw();
	}
}
bool Map::handleInput()
{
	for (auto& i : regions)
	{
		i.handleInput();
		return true;
	}
	// Some empty spot clicked, deselect the city.
	Region::selectedCity = nullptr;  
	return false;
}

void Map::updateAfterTurn()
{
	for ( auto& i : regions)
    {
		i.updateAfterTurn();
    }
}
Map::Map(std::vector<Region> R):
	regions(R)
{
}

std::vector<sf::Vector2f> getHexPos()
{
	std::vector<sf::Vector2f> hexPos;
	hexPos.push_back(sf::Vector2f(100,50));
	hexPos.push_back(sf::Vector2f(100,270));
	hexPos.push_back(sf::Vector2f(-90,160));
	return hexPos;
}
Region R(getHexPos(), elfFaction, grassLandsHexTexture);

 Map M= Map( vector<Region>{R});
