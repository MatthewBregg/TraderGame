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
	region(FactionEnum setFaction);	

private:
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
