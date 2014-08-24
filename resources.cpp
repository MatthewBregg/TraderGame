#include <iostream>

#include "resources.hpp"

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
 	food += reducedResources.food;
	wood += reducedResources.wood;
	iron += reducedResources.iron;
}