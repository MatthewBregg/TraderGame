#include <iostream>
//#include <stack>
#include "infrastructure.hpp"

#ifndef REGIONS_H
#define REGIONS_H

class region
{
public:
//should probably write a copy and descructor 
  region(Faction* owner= 0, Farm* f = nullptr, WoodMill* m = nullptr, Mine* mi = nullptr, City* c = nullptr, TraderCentre* tc = nullptr):farm(f),mill(m),mine(mi),city(c),tradeCentre(tc)
  {
    currentOwner = owner;
    origOwner = owner;
  };
private:
  Farm* farm;
  WoodMill* mill;
  Mine* mine;
  City* city;
  TraderCentre* tradeCentre;
  Faction* currentOwner;
  Faction* origOwner;
  // std::stack<Faction*> owners;
  
  

  

};

#endif /* REGIONS_H */
