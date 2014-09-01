#include "GlobalValues.h"

#include "Resources.h"

Resources::Resources(vector<unsigned int> setResources)
{
	assert(setResources.size() != TOTAL_RESOURCES + 1 && "Incorrect number of values provided for initialising resources.");
	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		resources.push_back(setResources.at(i));
	}
};

// Returns true if the caller has enough resources to be subtracted from
// reducedResources without going into the negative. Returns false otherwise.
bool Resources::canSubtract(const Resources& reducedResources)
{
	bool enoughResources = true;
	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		if (resources.at(i) < reducedResources.resources.at(i))
		{
			enoughResources = false;
			break;
		}
	}
	return enoughResources;
}

int Resources::get(ResourceEnum resource)
{
	return resources.at(resource);
}

void Resources::change(const Resources& howMuchChanged)
{
	for (int i = 0; i < TOTAL_RESOURCES; ++i)
	{
		resources.at(i) += howMuchChanged.resources.at(i);
	}
}

void Resources::change(ResourceEnum resource, int howMuchChanged)
{
	resources.at(resource) += howMuchChanged;
	if (resources.at(resource) < 0)
	{
		resources.at(resource) = 0;
	}
}
