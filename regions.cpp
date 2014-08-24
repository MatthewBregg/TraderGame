#include <iostream>
#include "regions.hpp"

<<<<<<< HEAD
int region::height = 80;
int region::length = 80;
=======

#include "regions.hpp"


region::region(FactionEnum setFaction):
	city(Resources(), 0),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)
{

};
>>>>>>> feb0795c92469ee569072d0e2fcbed35cd3a6ec8
