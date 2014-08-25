#include <iostream>
#include "regions.hpp"



int region::size = HEX_SIZE; 


region::region(FactionEnum setFaction):
	texture(nullptr),
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)

{
  //hexagon.setFillColor(sf::Color(150, 50, 250));
  //hexagon.setPosition(sf::Vector2f(50,10));
};

void region::draw(sf::RenderWindow& window)
{
  for ( auto& i : hexagons)
    {
  window.draw(i);
    }
}

void region::setTexture(sf::Texture* tex)
{
  for ( auto& i : hexagons)
    {
      i.setTexture(tex); 
    }
}

