#include <SFML/Graphics.hpp>
#include <iostream>
//#include <stack>
#include "infrastructure.hpp"
#include "city.hpp"
#include "faction.hpp"
#include "TradeCentre.hpp"


#ifndef REGIONS_H
#define REGIONS_H
#define HEX_SIZE 80

class region
{
public:
friend
//should probably write a copy and descructor 

  region(FactionEnum setFaction = nullFaction);
  void draw(sf::RenderWindow& window);
protected:
  void setPosition(const sf::Vector2f& pos);
  sf::Vector2f& getPosition() {return position;};
  void setTexture(sf::Texture* tex);
private:

  static int size;
  sf::CircleShape hexagon;
  sf::Texture* texture;
  
  // std::stack<Faction*> owners;

  City city;
  Farm farm;
  WoodMill mill;
  Mine mine;
  TradeCentre tradeCentre;
  FactionEnum currentOwner;
  FactionEnum origOwner;
  sf::Vector2f position;
  
  // std::stack<Faction*> owners;
  
};

#endif /* REGIONS_H */
