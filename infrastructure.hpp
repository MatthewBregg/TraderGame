#include <iostream>

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

class infrastructure
{
public:
  infrastructure(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock);
protected:

  unsigned int level;
  unsigned int maxPotential;
  double gold;
  int inStock;
};

class Farm: public infrastructure
{
public:
	Farm();
};

class WoodMill: public infrastructure
{
public:
	WoodMill();
};

class Mine: public infrastructure
{
public:
	Mine();
};
#endif /* INFRASTRUCTURE_H */
