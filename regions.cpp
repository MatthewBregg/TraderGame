#include <iostream>
#include "Texture.hpp"


#include "regions.hpp"



int Region::size = HEX_SIZE; 


Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture):
	texture(nullptr),
	city(Resources(), 0),
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

void Region::draw(sf::RenderWindow& window)
{
	for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		window.draw(*it);
	}
}

void Region::setTexture(sf::Texture* tex)
{
	for (std::vector<sf::Sprite>::iterator it = hexagons.begin(); it != hexagons.end(); ++it)
	{
		(*it).setTexture(*tex); 
    }
}

