#include <SFML/Graphics.hpp>
#include <iostream>
//#include <stack>
#include "Infrastructure.hpp"
#include "City.hpp"
#include "Faction.hpp"
#include "TradeCentre.hpp"
#include "Texture.hpp"
#include <vector>

#ifndef REGIONS_H
#define REGIONS_H

const double DEFAULT_HEX_SIZE = 256; //This should eventually be calculated by starting res
class World;

class Region
{
public:
	//should probably write a copy and descructor 
		// Why? If you mean saving, there should be a constructor that takes raw binary data, but that comes later.

	Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture, string cityName, double cityGold);
	void draw();
	void drawMenu();
	bool handleInput();
	void updateAfterTurn();
	
  static City* selectedCity;
  friend World;
protected:
	void setPosition(const sf::Vector2f& pos);

	void setTexture(sf::Texture* tex);
private:


	std::vector<sf::Sprite> hexagons;
    sf::Texture* texture;
  
	City city;
	Farm farm;
	WoodMill mill;
	Mine mine;
	TradeCentre tradeCentre;
	FactionEnum currentOwner;
	FactionEnum origOwner;

	sf::Sprite menu;

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
private:
	std::vector<Region> regions;

	// Returns the city offering the largest price for 1 unit of food.
	City* World::getMaxBuyingPrice();
	// Returns the farm asking for the smallest price for 1 unit of food. 
	Farm* World::getMinSellingPrice();
};

extern World world;

#endif /* REGIONS_H */
