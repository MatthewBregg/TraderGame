#include "GlobalValues.h"

#include "Resources.h"

Resources::Resources(int setFood, int setWood, int setSteel)
{
	resources[foodResource] = setFood;
	resources[woodResource] = setWood;
	resources[steelResource] = setSteel;
};

// Returns true if the caller has enough resources to be subtracted from
// reducedResources without going into the negative. Returns false otherwise.
bool Resources::canSubtract(const Resources& reducedResources)
{
	bool enoughResources = true;
	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		if (resources[i] < reducedResources.resources[i])
		{
			enoughResources = false;
			break;
		}
	}
	return enoughResources;
}

int Resources::get(ResourceEnum resource)
{
	return resources[resource];
}

void Resources::change(const Resources& howMuchChanged)
{
	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		resources[i] += howMuchChanged.resources[i];
	}
}

void Resources::change(ResourceEnum resource, int howMuchChanged)
{
	resources[resource] += howMuchChanged;
	if (resources[resource] < 0)
	{
		resources[resource] = 0;
	}
}
