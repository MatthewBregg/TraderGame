#ifndef GAMEVIEWS_H
#define GAMEVIEWS_H



#include "ButtonSfml.hpp"
#include "GlobalValues.hpp"
#include "Regions.hpp"



class GameViews
{
public:
  static void scroll(sf::Time Time);

  static void init();
  static void render();

  static void cleanUp();


};

#endif /* GAMEVIEWS_H */
