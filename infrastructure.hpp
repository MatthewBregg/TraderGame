#include <iostream>
#include "GlobalValues.hpp"

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

class Infrastructure
{
public:
  Infrastructure(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock);

  void draw(double x, double y);
  void refreshAfterTurn();
 
  double wouldSellFor();
  double upkeep();
  virtual string getName() = 0;
protected:
	sf::Text infrastructureText;

	unsigned int level;
	unsigned int maxPotential;
	double gold;
	unsigned int inStock;
};



class Farm: public Infrastructure
{
public:
	Farm(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock);
	virtual string getName();
};

class WoodMill: public Infrastructure
{
public:
	WoodMill(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock);
	virtual string getName();
};

class Mine: public Infrastructure
{
public:
	Mine(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock);
	virtual string getName();
};
#endif /* INFRASTRUCTURE_H */
