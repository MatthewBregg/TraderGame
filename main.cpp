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
#include "regions.hpp"

#include "GlobaValues.hpp"
#include "GameViews.hpp"



// Checks for input events (mouse, keyboard). 
void pollEvents(sf::RenderWindow* window)
{
    sf::Event event;

	if ((previousLeftClickState == false) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) // Clicked first
	{
		leftClickPressed = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) // Released
	{
		leftClickPressed = false;
	}
	previousLeftClickState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		
	mouseX = sf::Mouse::getPosition(*window).x;
	mouseY = sf::Mouse::getPosition(*window).y;
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

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Traps are the best");
	region R = region(nullFaction);
    while (window->isOpen())
    {
		pollEvents(window);
		
		window->clear(sf::Color(60, 60, 60));
		GameViews::render(window);
        window->display();
	R.draw(*window);
    }

	GameViews::cleanUp();
	delete window;
    return 0;
}
