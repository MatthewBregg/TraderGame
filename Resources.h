#include "GlobalValues.h"

#ifndef RESOURCES_H
#define RESOURCES_H

enum ResourceEnum
{
	foodResource = 0,
	woodResource = 1,
	steelResource = 2,
	TOTAL_RESOURCES = 3,
};

ResourceEnum getFirstResourceEnum();


class Resources
{
public:
	Resources(vector<unsigned int> setResources);
 
  
	// Returns true if the caller has enough resources to be subtracted from
	// reducedResources without going into the negative. Returns false otherwise.
	bool canSubtract(const Resources& reducedResources);

	int get(ResourceEnum resource) const;
	int get(int resource) const;
	void change(const Resources& howMuchChanged);
	void change(ResourceEnum resource, int howMuchChanged);

private:

	vector<int> resources;
};



#endif /* RESOURCES_H */
