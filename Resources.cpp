#include "GlobalValues.h"

#include "Resources.h"

Resources::Resources(int f, int w, int i):
	food(f),
	wood(w),
	steel(i)
{

};

// Returns true if the caller has enough resources to be subtracted from
// reducedResources without going into the negative. Returns false otherwise.
bool Resources::canSubtract(const Resources& reducedResources)
{
	return food >= reducedResources.food && wood >= reducedResources.wood && steel >= reducedResources.steel;
}
 
// Adds addedResources to the caller.
void Resources::add(const Resources& addedResources)
{
 	food += addedResources.food;
	wood += addedResources.wood;
	steel += addedResources.steel;
}
// Subtracts reducedResources number of resources from the caller.
void Resources::subtract(const Resources& reducedResources)
{
	food -= reducedResources.food;
	wood -= reducedResources.wood;
	steel -= reducedResources.steel;
}

unsigned int Resources::get(ResourceEnum resource)
{
	if (resource == foodResource)
	{
		return food;
	}
	else if (resource == woodResource)
	{
		return wood;
	}
	else if (resource == steelResource)
	{
		return steel;
	}
	else
	{
		assert(false && "Not existing resource requested.");
	}
	return 0;
}

void Resources::change(ResourceEnum resource, int howMuchChanged)
{
	if (resource == foodResource)
	{
		food += howMuchChanged;
		if (food < 0)
		{
			food = 0;
		}
	}
	else if (resource == woodResource)
	{
		wood += howMuchChanged;
		if (wood < 0)
		{
			wood = 0;
		}
	}
	else if (resource == steelResource)
	{
		steel += howMuchChanged;
		if (steel < 0)
		{
			steel = 0;
		}
	}
	else
	{
		assert(false && "Not existing resource requested.");
	}
}
