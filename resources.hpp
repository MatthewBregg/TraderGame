#include <iostream>
#ifndef RESOURCES_H
#define RESOURCES_H
class Resources
{
public:
  Resources(int f = 0, int w = 0, int i = 0);
 
  
  // Returns true if the caller has enough resources to be subtracted from
  // reducedResources without going into the negative. Returns false otherwise.
  bool canSubtract(const Resources& reducedResources);

  // Adds addedResources to the caller.
  void add(const Resources& addedResources);
  // Subtracts reducedResources number of resources from the caller.
  void subtract(const Resources& reducedResources);

private:

  unsigned int food;
  unsigned int wood;
  unsigned int iron;
};



#endif /* RESOURCES_H */
