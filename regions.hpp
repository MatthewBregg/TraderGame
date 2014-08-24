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
  region(Faction* owner= 0, Farm* f = nullptr, WoodMill* m = nullptr, Mine* mi = nullptr, City* c = nullptr, TradeCentre* tc = nullptr):farm(f),mill(m),mine(mi),city(c),tradeCentre(tc),hexagon(length,height),texture(nullptr)
  {
    currentOwner = owner;
    origOwner = owner;
  };
  region(FactionEnum setFaction);	
private:
  static int length;
  static int height;
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
  // std::stack<Faction*> owners;
  
};

#endif /* REGIONS_H */
