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

  Region(std::vector<sf::Vector2f> poses, FactionEnum setFaction, TextureIndex hexTexture);
  void draw();
  void updateAfterTurn();
protected:
  void setPosition(const sf::Vector2f& pos);

  void setTexture(sf::Texture* tex);
private:
  void resize(int s);
  static int size;
  std::vector<sf::Sprite> hexagons;
  sf::Texture* texture;
  
  // std::stack<Faction*> owners;

  City city;
  Farm farm;
  WoodMill mill;
  Mine mine;
  TradeCentre tradeCentre;
  FactionEnum currentOwner;
  FactionEnum origOwner;

  
  // std::stack<Faction*> owners;
  
};
class Map
{
public:
  void draw();
  void updateAfterTurn();
  Map(std::vector<Region> R);
private:
  std::vector<Region> regions;
};


//extern Region R;
extern Map M;

#endif /* REGIONS_H */
