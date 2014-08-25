#include <iostream>
#include "Texture.hpp"
#include "GlobalValues.hpp"


#include "regions.hpp"

std::vector<sf::Vector2f> getHexPos()
{
	std::vector<sf::Vector2f> hexPos;
	hexPos.push_back(sf::Vector2f(100,50));
	return hexPos;
}
Region R(getHexPos(), elfFaction, grassLandsHexTexture);

int Region::size = HEX_SIZE; 


Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture):
	texture(nullptr),
	city(Resources(40, 0, 0), 20),
	farm(1, 4, 10, 0),
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
	city.draw(200, 100);
	
	farm.draw(200, 200);
	//mill.draw(200, 210);
	//mine.draw(200, 260);
}
void Region::updateAfterTurn()
{
	city.refreshAfterTurn();

	farm.refreshAfterTurn();
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



