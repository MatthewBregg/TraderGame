#include <iostream>
#ifndef RESOURCES_H
#define RESOURCES_H
class Resources
{
public:
  Resources(int f = 0, int w =0, int i = 0):food(f),wood(w),iron(i){};
  unsigned int food;
  unsigned int wood;
  unsigned int iron;
};



#endif /* RESOURCES_H */
