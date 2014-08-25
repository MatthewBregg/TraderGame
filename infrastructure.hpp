#include <iostream>

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H
class Infrastructure
{
public:
  Infrastructure(int p=0, int l =0, int g =0, int s= 0):potential(p),level(l),gold(g),stock(s){};
protected:

  int potential;
  int level;
  int gold;
  int stock;
};
class Farm:Infrastructure
{

};

class WoodMill:Infrastructure
{

};

class Mine:Infrastructure
{

};
#endif /* INFRASTRUCTURE_H */
