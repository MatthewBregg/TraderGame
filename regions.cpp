#include <iostream>
#include "regions.hpp"



int Region::size = HEX_SIZE; 


Region::Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction):
	texture(nullptr),
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)

{
  for (auto& i : poses)
    {
      sf::CircleShape temp(size,6);
      temp.setPosition(i);
      hexagons.push_back(temp);
    }
  //hexagon.setFillColor(sf::Color(150, 50, 250));
  //hexagon.setPosition(sf::Vector2f(50,10));
};

Region::Region(std::initializer_list<sf::Vector2f> poses, FactionEnum setFaction):
	texture(nullptr),
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)

{

  for (auto& i : poses)
    {
      sf::CircleShape temp(size,6);
      temp.setPosition(i);
      hexagons.push_back(temp);
    }
  
  //hexagon.setFillColor(sf::Color(150, 50, 250));
  //hexagon.setPosition(sf::Vector2f(50,10));
};

void Region::draw(sf::RenderWindow& window)
{
  for ( auto& i : hexagons)
    {
  window.draw(i);
    }
}

void Region::setTexture(sf::Texture* tex)
{
  for ( auto& i : hexagons)
    {
      i.setTexture(tex); 
    }
}

