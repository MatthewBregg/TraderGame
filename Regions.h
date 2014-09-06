#include <SFML/Graphics.hpp>
#include "Infrastructure.h"
#include "City.h"
#include "Faction.h"
#include "TradeCentre.h"
#include "Texture.h"
#include "Graph.h"
#include "ClickableRectangle.h"
#include "GlobalValues.h"

#ifndef REGIONS_H
#define REGIONS_H

const double DEFAULT_HEX_SIZE = 256; //This should eventually be calculated by starting res
class World;

class Region
{
public:

	Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold);
	void draw();
	bool handleInput();
	void drawMenu();
	bool handleMenuInput();
	void updateAfterTurn();

        friend World;
protected:
	void greyoutBuyButtons();
	void setPosition(const sf::Vector2f& pos);
	void setTexture(sf::Texture* tex);

	static Region* selectedRegion;

	std::vector<sf::Sprite> hexagons;
    sf::Texture* texture;
  
	City city;
	Farm farm;
	WoodMill woodmill;
	Mine mine;
	TradeCentre tradeCentre;
	FactionEnum currentOwner;
	FactionEnum origOwner;

	static TexturedRectangle regionMenu;

	static TexturedRectangle playerResourceMenu;
	static void drawPlayerResourceMenu();
	static Resources playerResources;
	static double playerGold;
};


class World
{
public:
	World();

	void draw();
	bool handleInput();
	void drawMenu();
	bool handleMenuInput();

	void handleTrading();
	void updateAfterTurn();

	friend Region;
protected:
	
	Graph populationGraph;
	Graph foodPriceGraph;

	std::vector<Region> regions;
	// Returns the resource that would be payed for the most. For example, city a pays
	// (1, 5, 6) for each resource. City b pays (7, 3, 4). The most wanted resource is the 
	// first one, as someone would pay 7 gold for it.
	// Only elements for whom a new deal can occur are considered.
	ResourceEnum getMostWantedResource(const vector<bool>* aNewDealCanOccur);
	// Returns the city offering the largest price for 1 unit of food.
	Region* getMaxBuyingPrice(ResourceEnum resource);
	// Returns the infrastructure asking the smallest price for the given resource.
	Infrastructure* getMinSellingPrice(ResourceEnum resource, Region* startingRegion);
};

extern World world;

#endif /* REGIONS_H */
