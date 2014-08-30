#ifndef GAMEVIEWS_H
#define GAMEVIEWS_H



#include "ButtonSfml.h"
#include "GlobalValues.h"
#include "Regions.h"



class GameViews
{
public:
  static void scroll(const sf::Time& Time );

  static void init();
  static void render();

  static void cleanUp();


};

#endif /* GAMEVIEWS_H */
