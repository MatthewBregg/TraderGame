#include <iostream>
#ifndef RESOURCES_H
#define RESOURCES_H
class Resources
{
public:
	Resources(int f, int w, int i);
 
  
	// Returns true if the caller has enough resources to be subtracted from
	// reducedResources without going into the negative. Returns false otherwise.
	bool canSubtract(const Resources& reducedResources);

	// Adds addedResources to the caller.
	void add(const Resources& addedResources);
	// Subtracts reducedResources number of resources from the caller.
	void subtract(const Resources& reducedResources);

  
	unsigned int getFood();
	void addFood(int foodAdded);
	void subtractFood(int foodLost);

private:

  unsigned int food;
  unsigned int wood;
  unsigned int iron;
};



#endif /* RESOURCES_H */
