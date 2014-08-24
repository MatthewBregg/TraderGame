#include <iostream>


#include "regions.hpp"


region::region(FactionEnum setFaction):
	city(),
	farm(),
	mill(),
	mine(),
	tradeCentre(),
	currentOwner(setFaction),
	origOwner(setFaction)
{

};