#include <iostream>
#include <stack>

#ifndef REGIONS_H
#define REGIONS_H

class region
{
public:
  region(Faction* owner= 0, Farm* f = nullptr, WoodMill* m = nullptr, Mine* mi = nullptr, City* c = nullptr, TraderCentre* tc = nullptr):farm(f),mill(m),mine(mi),city(c),tradeCentre(tc)
  {
    owners.push_back(owner);
  };
private:
  Farm* farm;
  Woodmill* mill;
  Mine* mine;
  City* city;
  TraderCentre* tradeCentre;
  std::stack<faction*> owners;
  
  

  

};

#endif /* REGIONS_H */
