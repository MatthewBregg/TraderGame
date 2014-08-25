#include <iostream>
#include "Texture.hpp"
#include "GlobalValues.hpp"


#include "Regions.hpp"

std::vector<sf::Vector2f> getHexPos()
{
	std::vector<sf::Vector2f> hexPos;
	hexPos.push_back(sf::Vector2f(100,50));
	hexPos.push_back(sf::Vector2f(100,270));
	hexPos.push_back(sf::Vector2f(-90,160));
	return hexPos;
}
Region R(getHexPos(), elfFaction, grassLandsHexTexture);

int Region::size = DEFAULT_HEX_SIZE; 
void Region::resize(int s)
{

  //todo

}


Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture):
	texture(nullptr),
	city("Bronx", Resources(40, 0, 0), 20),
	farm(1, 6, 10, 0),
	mill(0, 0, 0, 0),
	mine(0, 0, 0, 0),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)

{
	for (std::vector<sf::Vector2f>::iterator it = poses.begin(); it != poses.end(); ++it)
	{
		sf::Sprite temp;
		temp.setTexture(*getTexture(hexTexture));
		temp.setPosition(*it);
		hexagons.push_back(temp);
	}
};

void Region::draw()
{
  for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		window->draw(*it);
	}
	city.draw(400, 100);
	
	farm.draw(400, 200);
	//mill.draw(400, 210);
	//mine.draw(400, 260);

	// To check if there are any bugs when exchanging gold.
	drawText(strPlusX("Total gold: ", city.getGold() + farm.getGold()), 150, 500);
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



