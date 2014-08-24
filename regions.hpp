#include <SFML/Graphics.hpp>
#include <iostream>
//#include <stack>
#include "infrastructure.hpp"
#include "city.hpp"
#include "faction.hpp"
#include "TradeCentre.hpp"


#ifndef REGIONS_H
#define REGIONS_H

class region
{
public:

//should probably write a copy and descructor 

  region(FactionEnum setFaction = nullFaction);
  void draw(sf::RenderWindow& window);
private:

  static int size;
  sf::CircleShape hexagon;
  sf::Texture* texture;
  
  // std::stack<Faction*> owners;

  City city;
  Farm farm;
  WoodMill mill;
  Mine mine;
  TradeCentre tradeCentre;
  FactionEnum currentOwner;
  FactionEnum origOwner;
  bool textSet;
  
  // std::stack<Faction*> owners;
  
};

#endif /* REGIONS_H */
