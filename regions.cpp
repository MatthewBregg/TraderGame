#include <iostream>
#include "regions.hpp"


int region::size = 80; 

region::region(FactionEnum setFaction):
	hexagon(size,6),
	texture(nullptr),
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)
{
hexagon.setFillColor(sf::Color(150, 50, 250));
 hexagon.setPosition(sf::Vector2f(10, 50));
};

void region::draw(sf::RenderWindow& window)
{
  window.draw(hexagon);
}
