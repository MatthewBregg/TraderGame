#include <iostream>
#include "regions.hpp"



int region::size = HEX_SIZE; 





region::region(FactionEnum setFaction):
	hexagon(size,6),
	texture(nullptr),
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction),
	position(sf::Vector2f(10,50))
{
hexagon.setFillColor(sf::Color(150, 50, 250));
 hexagon.setPosition(position);
};

void region::draw(sf::RenderWindow& window)
{
  window.draw(hexagon);
}
void region::setPosition(const sf::Vector2f& pos)
{
  position = pos;
  hexagon.setPosition(pos);
}
