#include <iostream>

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H
class infrastructure
{
public:
  infrastructure(int p=0, int l =0, int g =0, int s= 0):potential(p),level(l),gold(g),stock(s){};
protected:

  int potential;
  int level;
  int gold;
  int stock;
};
class Farm:infrastructure
{

};

class WoodMill:infrastructure
{

};

class Mine:infrastructure
{

};
#endif /* INFRASTRUCTURE_H */
