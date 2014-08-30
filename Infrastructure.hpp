#include <iostream>
#include "GlobalValues.hpp"

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

class Infrastructure
{
public:
	Infrastructure(unsigned int setLevel, unsigned int setMaxLevel, double setGold, int setStock, int xPos, int yPos);

	void draw();
	void drawMenu(double x, double y);
	// Updates the infrastructure and returns the upkeep for that turn.
	double refreshAfterTurn();
 
	double wouldSellFor();
	double upkeep();
	void acceptDeal();
	double getGold();

  virtual string getName() = 0;
protected:
	sf::Text infrastructureText;

	unsigned int level;
	unsigned int maxLevel;
	double gold;
	unsigned int inStock;
};



class Farm: public Infrastructure
{
public:
	Farm(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos);
	virtual string getName();
};

class WoodMill: public Infrastructure
{
public:
	WoodMill(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos);
	virtual string getName();
};

class Mine: public Infrastructure
{
public:
	Mine(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock, int xPos, int yPos);
	virtual string getName();
};
#endif /* INFRASTRUCTURE_H */
