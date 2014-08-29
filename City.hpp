#include <iostream>
#include "Resources.hpp"
#include "GlobalValues.hpp"
#ifndef CITY_H
#define CITY_H

class City
{
public:
	City(string setName, Resources r, int g, int xPos, int yPos);

	void draw(double x, double y);
	void drawMenu(double x, double y);
	void refreshAfterTurn(double upkeepFromInfrastructures);
	
	double getBuyingPrice();
	unsigned int getPopulationFoodReq();
	double getPopulationChange();
	bool cityWouldAcceptDeal(double offeredPrice);
	void acceptDeal(double price);
	double getGold();

private:
	string name;
	Resources resources;
	double gold;
	unsigned int population;

	sf::Sprite citySprite;


	void updatePopulation();

};


#endif /* CITY_H */
