#ifndef GAMEVIEWS_H
#define GAMEVIEWS_H



#include "ButtonSfml.h"
#include "GlobalValues.h"
#include "Regions.h"



class GameViews
{
public:
  static void scroll();
  static void resizeCheck();

  static void init();
  static void render();
  static void zoom(int delta);
  static void cleanUp();


};

#endif /* GAMEVIEWS_H */
