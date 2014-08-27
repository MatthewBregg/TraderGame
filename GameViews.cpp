#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;
#include "Regions.hpp"
#include "Texture.hpp"
#include "EndTurn.hpp"

#include "GameViews.hpp"

// The different parts of the programs' execution.
enum GameView
{
	startMenuView,
	mapView,

};
GameView gameView = mapView;


void GameViews::init()
{

}

void GameViews::render()
{
	if (gameView == mapView)										
	{
		M.draw();
		EndTurn::draw();
		EndTurn::refresh();
	}
}
void GameViews::scroll(const sf::Clock clock)
{
  //71 is left, 72 is right, 73 is up, 74 is downs

  if (keys[71])
    {
      view->move(-SCROLL_SPEED*clock.getElapsedTime().asMicroseconds(),0);
      window->setView(*view);
    }
  if (keys[72])
    {
      view->move(SCROLL_SPEED*clock.getElapsedTime().asMicroseconds(),0);
      window->setView(*view);
    }
  if (keys[73])
    {
      view->move(0,-SCROLL_SPEED*clock.getElapsedTime().asMicroseconds());
      window->setView(*view);
    }
  if (keys[74])
    {
      view->move(0,SCROLL_SPEED*clock.getElapsedTime().asMicroseconds());
      window->setView(*view);
    }
  if (keys[17])
    {
      view->setCenter(400,300); //These should later not be hardcoded, to better handle resizing.
      window->setView(*view);
    }

}
void GameViews::cleanUp()
{

}
