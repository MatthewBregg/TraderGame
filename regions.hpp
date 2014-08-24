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
private:
  Farm* farm;
  static int length;
  static int height;
  WoodMill* mill;
  Mine* mine;
  City* city;
  TradeCentre* tradeCentre;
  Faction* currentOwner;
  Faction* origOwner;
  sf::CircleShape hexagon;
  sf::Texture* texture;
  
  // std::stack<Faction*> owners;
  
  

  

};

#endif /* REGIONS_H */
