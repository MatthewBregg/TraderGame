#include "infrastructure.hpp"


infrastructure::infrastructure(unsigned int setLevel, unsigned int setMaxPotential, double setGold, int setStock):
  level(setLevel),
  maxPotential(setMaxPotential),
  gold(setGold),
  inStock(setStock)
{

};

Farm::Farm():
	infrastructure(0, 0, 0, 0)
{

}
WoodMill::WoodMill():
	infrastructure(0, 0, 0, 0)
{

}
Mine::Mine():
	infrastructure(0, 0, 0, 0)
{

}