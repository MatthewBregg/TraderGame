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

	sf::Clock keyClock; //we need something like this to keep movement from being jerky
    while (window->pollEvent(event))
    {
      //Put keyboard events here
      GameViews::scroll(keyClock);		
      keyClock.restart();
        if (event.type == sf::Event::Closed)
            window->close();
		if (event.type == sf::Event::MouseWheelMoved)
		{
			mouseScroll = event.mouseWheel.delta; // Negative or positive depending on which way the player scrolls.
		}
		if (event.type == sf::Event::KeyPressed)
		{
			keys[event.key.code] = true;
			keyClock.restart();
	

		}


		if (event.type == sf::Event::KeyReleased)
		{
			keys[event.key.code] = false;
			keyClock.restart();
		}
	
	}
    

}

int main()
{
	GameViews::init();

	window = new sf::RenderWindow(sf::VideoMode(getWindowWidth(), getWindowHeight()), "Traps are the best");
	view = new sf::View(sf::Vector2f(400,300), sf::Vector2f(800,600));
	window->setView(*view);
	
	
    while (window->isOpen())
    {

      window->setView(*view);
		pollEvents(window);
		
		window->clear(sf::Color(60, 60, 60));
		GameViews::render();
        window->display();

    }

	GameViews::cleanUp();
	delete window;
    return 0;
}
