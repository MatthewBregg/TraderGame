#include <iostream>
#include "Resources.h"
#include "GlobalValues.h"
#include "ClickableRectangle.h"
#include "ButtonSfml.h"
#ifndef CITY_H
#define CITY_H

class City : public ClickableRectangle
{
public:
	City(string setName, Resources r, int g, int xPos, int yPos);

	void draw();
	void drawMenu(double x, double y);
	void drawSellingButton(double x, double y);
	bool isSellingButtonClickedOn();
	void refreshAfterTurn();
	
	double getBuyingPrice();
	unsigned int getPopulationFoodReq();
	double getPopulationChange();
	bool cityWouldAcceptDeal(double offeredPrice);
	void acceptDeal(double price);
	double getGold();
	void addGold(double howMuch);
	unsigned int getPopulation();
private:
	string name;
	Resources resources;
	double gold;
	unsigned int population;

	sf::Sprite citySprite;
	ButtonSfml sellToButton;


	void updatePopulation();

};


#endif /* CITY_H */
