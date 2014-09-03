#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;
#include "Regions.h"
#include "Texture.h"
#include "EndTurn.h"

#include "GameViews.h"

// The different parts of the programs' execution.
enum GameView
{
	startMenuView,
	mapView,

};
GameView gameView = mapView;


void GameViews::init()
{
  mapSize.setOrigin((-getWindowWidth()/2)+mapSize.getSize().x/2,-(getWindowHeight()/2-mapSize.getSize().y/2));
  //Should center the map boundaries.

}

void GameViews::render()
{
	if (gameView == mapView)										
	{
		// If "end turn" is clicked on, ignore the input for the map. 
		// Since the map might interpret the click as the player trying
		// to select something.
		if (EndTurn::handleInput())
		{
		}
		else if (world.handleInput())
		{

		}

		window->setView(*view);
		world.draw();

		window->setView(window->getDefaultView());
		EndTurn::draw();
		world.drawMenu();
		window->setView(*view);
	}
}
void GameViews::resizeCheck()
{
    static sf::Clock count;
    static bool fullscreen = false;
    static sf::Vector2u oldsize(sf::Vector2u(800,600));
    if (((keys[42] && keys[5]) || (keys[38] && keys[5])) && count.getElapsedTime() > sf::seconds(1))
	{
	    count.restart();
	    if (!fullscreen)
		{
		    oldsize=window->getSize();
		    window->setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().height * 1.333, sf::VideoMode::getDesktopMode().height));
		    fullscreen = true;
		}
	    else
		{

		    window->setSize(sf::Vector2u(800,600)); //Return to normal window size
		    fullscreen = false;
		}
	    return;

	}
    if (abs(((double)view->getSize().x/(double)view->getSize().y) - 1.3333) > .1)
	{
	    //If window is ever not 4/3, then fix that.
	    window->setSize(sf::Vector2u((int)(window->getSize().y*1.33),(window->getSize().y)));
	    return;
	}
}
void GameViews::scroll(const sf::Time& clock)
{
  static sf::Time lasttime(sf::seconds(0));
  static int oldchange(0);
   int change = ((((clock + lasttime)).asMicroseconds())/2)/100 * SCROLL_SPEED;
  change = (change+oldchange)/2;
	//71 is left, 72 is right, 73 is up, 74 is downs
   if ( change > 50 )
     {
       change = 50;
     }  
   lasttime = clock;
   // std::cout << "POS IS " << view->getCenter().x << " " << view->getCenter().y << std::endl; 
   // cout << "Change is " << change << endl;

  if (keys[71])
    {
      view->move(-change,0);
      if ( !mapSize.getGlobalBounds().contains(view->getCenter()))
	{

	  view->move(change,0);

	}
      window->setView(*view);
    }
  if (keys[72])
    {
      view->move(change,0);
      if ( !mapSize.getGlobalBounds().contains(view->getCenter()))
	{

	  view->move(-change,0);

	}
      window->setView(*view);
    }
  if (keys[73])
    {
      view->move(0,-change);
      if ( !mapSize.getGlobalBounds().contains(view->getCenter()))
	{

	  view->move(0,change);

	}
      window->setView(*view);
    }
  if (keys[74])
    {
      view->move(0,change);
      if ( !mapSize.getGlobalBounds().contains(view->getCenter()))
	{

	  view->move(0,-change);

	}
      window->setView(*view);
    }
  if (keys[17])		// What is this?
    {
      view->setCenter(400,300); //These should later not be hardcoded, to better handle resizing.
      window->setView(*view);
    }

}
void GameViews::cleanUp()
{

}
