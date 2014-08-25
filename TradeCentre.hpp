#include <iostream>
#include "Resources.hpp"
#ifndef TRADECENTRE_H
#define TRADECENTRE_H
class TradeCentre
{
public:
  TradeCentre():resources(0,0,0){};  
  TradeCentre(Resources& r):resources(r){};
private:
  Resources resources;
};


#endif /* TRADECENTRE_H */
