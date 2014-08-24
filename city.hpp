#include <iostream>
#include "resources.hpp"
#ifndef CITY_H
#define CITY_H
class City
{
public:
  City():resources(0,0,0),gold(0){};
  City(Resources& r, int g = 0):resources(r),gold(g){};
private:
  Resources resources;
  double gold;
};


#endif /* CITY_H */
