#include "Resources.h"
#include <array>
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
	void drawSellingButtons();
	bool isSellingButtonClickedOn(ResourceEnum resource);
	void refreshAfterTurn();
	
	double getBuyingPrice(ResourceEnum resource);

	unsigned int getPopulationFoodReq();
	double getPopulationChange();
	bool wouldAcceptDeal(ResourceEnum resourceTraded, double offeredPrice);
	void acceptDeal(ResourceEnum resourceTraded, double price);
	double getGold();
	void addGold(double howMuch);
	unsigned int getPopulation();
private:
	string name;
	Resources resources;
	double gold;
	unsigned int population;
	unsigned int soldiers;

	sf::Sprite citySprite;
	array<ButtonSfml, TOTAL_RESOURCES> sellToButtons;

	void updatePopulation();
	
	double foodBuyingPrice();
	double woodBuyingPrice();
	double steelBuyingPrice();
};


#endif /* CITY_H */
