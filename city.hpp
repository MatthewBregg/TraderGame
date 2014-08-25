#include <iostream>
#include "Resources.hpp"
#ifndef CITY_H
#define CITY_H

class City
{
public:
	City(Resources r, int g);

	void draw(double x, double y);
	void refreshAfterTurn();

private:
	Resources resources;
	double gold;
	unsigned int population;

	sf::Text populationText;

	void updatePopulation();

	unsigned int getPopulationFoodReq();
	double getPopulationChange();
};


#endif /* CITY_H */
