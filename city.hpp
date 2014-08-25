#include <iostream>
#include "Resources.hpp"
#ifndef CITY_H
#define CITY_H

class City
{
public:
  City(Resources r, int g);

  void draw();
  void refreshAfterTurn();

private:
  Resources resources;
  double gold;
  unsigned int population;

	sf::Text populationText;

};


#endif /* CITY_H */
