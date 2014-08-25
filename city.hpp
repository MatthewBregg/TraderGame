#include <iostream>
#include "Resources.hpp"
#ifndef CITY_H
#define CITY_H
class City
{
public:
  City(Resources r , int g = 0):resources(r),gold(g){};


private:
  Resources resources;
  double gold;
};


#endif /* CITY_H */
