#include "Resources.h"
#include "GlobalValues.h"
#include "ClickableRectangle.h"
#include "ButtonSfml.h"
#include "Faction.h"
#ifndef CITY_H
#define CITY_H

class City : public ClickableRectangle
{
public:
	City(string setName, Resources r, int g, int xPos, int yPos, FactionEnum setFaction);

	void draw();
	void draw(const Resources player);
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
	FactionEnum factionIndex;
	sf::Sprite citySprite;
	array<ButtonSfml, TOTAL_RESOURCES> sellToButtons;
	void greyOutSellingButtons(const Resources& player);
	void updatePopulation();
	// Creates soldiers if there is enough wood and steel (and population).
	void updateSolders();

	double foodBuyingPrice();
	double woodBuyingPrice();
	double steelBuyingPrice();
};


#endif /* CITY_H */
