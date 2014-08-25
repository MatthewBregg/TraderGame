#include <SFML/Graphics.hpp>
#include <iostream>
//#include <stack>
#include "infrastructure.hpp"
#include "city.hpp"
#include "resources.hpp"
#include "faction.hpp"
#include "TradeCentre.hpp"
#include <vector>
#include <initializer_list>


#ifndef REGIONS_H
#define REGIONS_H
#define HEX_SIZE 80

class Region
{
public:
//should probably write a copy and descructor 

  Region(std::initializer_list<sf::Vector2f> poses,FactionEnum setFaction = nullFaction);
  Region(std::vector<sf::Vector2f> poses,FactionEnum setFaction = nullFaction);
  void draw(sf::RenderWindow& window);
protected:
  void setPosition(const sf::Vector2f& pos);

  void setTexture(sf::Texture* tex);
private:

  static int size;
  std::vector<sf::CircleShape> hexagons;
  sf::Texture* texture;
  
  // std::stack<Faction*> owners;

  City city;
  Farm farm;
  WoodMill mill;
  Mine mine;
  TradeCentre tradeCentre;
  FactionEnum currentOwner;
  FactionEnum origOwner;

  
  // std::stack<Faction*> owners;
  
};

#endif /* REGIONS_H */
