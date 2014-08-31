#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Infrastructure.h"
#include "City.h"
#include "Faction.h"
#include "TradeCentre.h"
#include "Texture.h"
#include "Graph.h"

#ifndef REGIONS_H
#define REGIONS_H

const double DEFAULT_HEX_SIZE = 256; //This should eventually be calculated by starting res
class World;

class Region
{
public:
	//should probably write a copy and descructor 
		// Why? If you mean saving, there should be a constructor that takes raw binary data, but that comes later.
  //Originally had pointers, now we don't so not needed

	Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold);
	void draw();
	bool handleInput();
	void drawMenu();
	bool handleMenuInput();
	void updateAfterTurn();

  friend World;
protected:
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

	sf::Sprite menu;
	
	static Resources playerResources;
	static double playerGold;
};


class World
{
public:
	World();

  void draw();
  void drawMenu();
  bool handleInput();

  void handleTrading();
  void updateAfterTurn();
protected:


	Graph populationGraph;

	std::vector<Region> regions;

	// Returns the city offering the largest price for 1 unit of food.
	City* getMaxBuyingPrice();
	// Returns the farm asking for the smallest price for 1 unit of food. 
	Farm* getMinSellingPrice();
};

extern World world;

#endif /* REGIONS_H */
