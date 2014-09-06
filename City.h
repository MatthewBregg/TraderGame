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
	
	bool wouldAcceptDeal(ResourceEnum resourceTraded, double offeredPrice);
	void acceptDeal(ResourceEnum resourceTraded, double price);
	// Set the lowest price the city can get. This will be used as the price 
	// at which the city will buy from the player. Done here so it is only refreshed once.
	// If city can get food at 0.4 at the start of the turn, player will have to 
	// sell at that price for the whole turn. Otherwise, if player buys 1 food from 
	// farm, the price would go up (as farm would no longer have as much food in stock).
	// Thus the min price would increase, and player could make money just by buying
	// things from infrastructures and selling right off to cities. 
	void setNewLowestPrice(ResourceEnum resourceTraded, double newPrice);

	// The price at which the city buys from infrastructures.
	double getBuyingPrice(ResourceEnum resource);
	// The price at which the city buys from the player.
	double getPlayerBuyingPrice(ResourceEnum resource);
	unsigned int getPopulationFoodReq();
	double getPopulationChange();
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
	// Set the lowest price the city can get for each resource.
	vector<double> lowestPrice;

	void greyOutSellingButtons(const Resources& player);
	void updatePopulation();
	// Creates soldiers if there is enough wood and steel (and population).
	void updateSolders();

	double foodBuyingPrice();
	double woodBuyingPrice();
	double steelBuyingPrice();
};


#endif /* CITY_H */
