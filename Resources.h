#include "GlobalValues.h"

#ifndef RESOURCES_H
#define RESOURCES_H

enum ResourceEnum
{
	foodResource,
	woodResource,
	steelResource,
	TOTAL_RESOURCES,
};

class Resources
{
public:
	Resources(vector<unsigned int> setResources);
 
  
	// Returns true if the caller has enough resources to be subtracted from
	// reducedResources without going into the negative. Returns false otherwise.
	bool canSubtract(const Resources& reducedResources);

	int get(ResourceEnum resource);

	void change(const Resources& howMuchChanged);
	void change(ResourceEnum resource, int howMuchChanged);

private:

	vector<int> resources;
};



#endif /* RESOURCES_H */
