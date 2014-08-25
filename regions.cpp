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
	city(Resources(), 20),
	farm(),
	mill(),
	mine(),
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
	city.draw();
}
void Region::updateAfterTurn()
{
	city.refreshAfterTurn();
}


void Region::setTexture(sf::Texture* tex)
{
	for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		(*it).setTexture(*tex); 
    }
}



