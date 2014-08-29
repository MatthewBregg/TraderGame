#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;


#include "ButtonSfml.hpp"
#include "Regions.hpp"

#include "GlobalValues.hpp"
#include "GameViews.hpp"

sf::Clock fpsTime;
sf::Time getAverageFPSTime()
{
  static long long fpscount = 1;
  sf::Time temp = runtime.getElapsedTime() / fpscount;
  if ( runtime.getElapsedTime() > sf::seconds(500))
    {
      runtime.restart();
    }
  return temp;
}

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
		

sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);


 mouseX = worldPos.x;
 mouseY = worldPos.y;
	mouseScroll = 0; // Reset it, will be set later if MouseWheelMoved event has happened.


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
	
	}
    

}

int main()
{

	GameViews::init();

	window = new sf::RenderWindow(sf::VideoMode(getWindowWidth(), getWindowHeight()), "Traps are the best");
	view = new sf::View(sf::Vector2f(400,300), sf::Vector2f(800,600));
	window->setView(*view);

	window->setFramerateLimit(120);	
	
	while (window->isOpen())
	  {

	    window->setView(*view);
	    pollEvents(window);
		
	    window->clear(sf::Color(60, 60, 60));
	    GameViews::render();
	    GameViews::scroll(getAverageFPSTime());		
	    window->display();
	    fpsTime.restart();

	  }

	GameViews::cleanUp();
	delete window;
    return 0;
}
