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

const int DEFAULT_HEX_SIZE = 80; //This should eventually be calculated by starting res

class Region
{
public:
	//should probably write a copy and descructor 
		// Why? If you mean saving, there should be a constructor that takes raw binary data, but that comes later.

	Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture);
	void draw();
	void drawMenu();
	bool handleInput();
	void updateAfterTurn();
	
  static City* selectedCity;

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
class Map
{
public:
  void draw();
  bool handleInput();
  void updateAfterTurn();
  Map(std::vector<Region> R);
private:
  std::vector<Region> regions;
};


//extern Region R;
extern Map M;

#endif /* REGIONS_H */
