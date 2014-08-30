#include <iostream>

#include "Resources.h"

Resources::Resources(int f, int w, int i):
	food(f),
	wood(w),
	iron(i)
{

};


// Returns true if the caller has enough resources to be subtracted from
// reducedResources without going into the negative. Returns false otherwise.
bool Resources::canSubtract(const Resources& reducedResources)
{
	return food >= reducedResources.food && wood >= reducedResources.wood && iron >= reducedResources.iron;
}
 
// Adds addedResources to the caller.
void Resources::add(const Resources& addedResources)
{
 	food += addedResources.food;
	wood += addedResources.wood;
	iron += addedResources.iron;
}
// Subtracts reducedResources number of resources from the caller.
void Resources::subtract(const Resources& reducedResources)
{
	subtractFood(reducedResources.food);
	wood += reducedResources.wood;
	iron += reducedResources.iron;
}

unsigned int Resources::getFood()
{
	return food;
}
void Resources::addFood(int foodAdded)
{
	food += foodAdded;
}
void Resources::subtractFood(int foodLost)
{
	if (food < foodLost)
	{
		food = 0;
	}
	else
	{
		food -= foodLost;
	}
}
