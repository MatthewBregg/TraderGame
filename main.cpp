#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;


#include "ButtonSfml.h"
#include "Regions.h"

#include "GlobalValues.h"
#include "GameViews.h"

sf::Clock fpsTime;

// sf::Time getAverageFPSTime()
// {
//   static long long fpscount = 1;
//   static sf::Time fpsSum(sf::seconds(0));
//   fpsSum += fpsTime.getElapsedTime();
//   fpscount++;
//   sf::Time temp = (fpsSum / fpscount);
  
 
//   if ( fpsSum.asSeconds() > 2)
//     {


//       fpsSum=sf::seconds(0);
//       fpscount = 1;
//     }
//   return temp;
// }

// Checks for input events (mouse, keyboard). 

void pollEvents(sf::RenderWindow* window)
{
    sf::Event event;

	leftClickPressed = false;
	if ((previousLeftClickState == false) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) // Click down for the first time.
	{
		leftClickPressed = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) // Released
	{
		leftClickPressed = false;
	}
	previousLeftClickState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		
window->setView(*view);
sf::Vector2i pixelPosRelative = sf::Mouse::getPosition(*window);
sf::Vector2f worldPosRelative = window->mapPixelToCoords(pixelPosRelative);
 window->setView(*DEFAULT_VIEW);
sf::Vector2i pixelPosAbsolute = sf::Mouse::getPosition(*window);
sf::Vector2f worldPosAbsolute = window->mapPixelToCoords(pixelPosAbsolute);
 window->setView(*view);
 if ( window->getSize().y != 0 && window->getSize().x != 0)
     {
	 mouseX = worldPosAbsolute.x; //sf::Mouse::getPosition(*window).x;
	 relativeMouseX = worldPosRelative.x;
	 mouseY = worldPosAbsolute.y; //sf::Mouse::getPosition(*window).y;
	 relativeMouseY = worldPosRelative.y;
	 mouseScroll = 0; // Reset it, will be set later if MouseWheelMoved event has happened.
     }



    while (window->pollEvent(event))
    {

	
        if (event.type == sf::Event::Closed)
            window->close();
	if (event.type == sf::Event::MouseWheelMoved)
	    {
		mouseScroll = event.mouseWheel.delta; // Negative or positive depending on which way the player scrolls.
	    }
	if (event.type == sf::Event::KeyPressed)
	    {

		keys[event.key.code] = true;
	    }


	if (event.type == sf::Event::KeyReleased)
	    {
		keys[event.key.code] = false;

	    }
	if (event.type == sf::Event::Resized)
	    {

	    }
	
    }
}

int main()
{
   
	GameViews::init();

	window = new sf::RenderWindow(sf::VideoMode(getWindowWidth(), getWindowHeight()), "Traps are the best");
	view = new sf::View(sf::Vector2f(getWindowWidth() / 2, getWindowHeight() / 2), sf::Vector2f(getWindowWidth(), getWindowHeight()));
	DEFAULT_VIEW = new sf::View(window->getDefaultView());
	window->setView(*view);

	window->setFramerateLimit(60);	

	while (window->isOpen())
	  {

	    window->setView(*view);
	    pollEvents(window);
		
	    window->clear(sf::Color(60, 60, 60));
	    GameViews::render();
	    GameViews::resizeCheck();
	    //	    sf::Time avgFPS = getAverageFPSTime();
	    GameViews::scroll(fpsTime.getElapsedTime());		
	    //   window->draw(mapSize); //Turn this on to see the map boundaries
	    window->display();
	    fpsTime.restart();




	  }

	GameViews::cleanUp();
	delete window;
    return 0;
}
