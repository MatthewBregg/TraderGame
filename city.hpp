#include <iostream>
#include "Resources.hpp"
#include "GlobalValues.hpp"
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

	void updatePopulation();

	unsigned int getPopulationFoodReq();
	double getPopulationChange();
};


#endif /* CITY_H */
