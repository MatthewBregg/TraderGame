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

  double upkeep();
  virtual string getName() = 0;
protected:
	sf::Text infrastructureText;

	unsigned int level;
	unsigned int maxPotential;
	double gold;
	int inStock;
};

class Farm: public Infrastructure
{
public:
	Farm();
	virtual string getName();
};

class WoodMill: public Infrastructure
{
public:
	WoodMill();
	virtual string getName();
};

class Mine: public Infrastructure
{
public:
	Mine();
	virtual string getName();
};
#endif /* INFRASTRUCTURE_H */
