#include "GlobalValues.h"


sf::RenderWindow* window;
sf::View* view;

string getResourcePath()
{
	return RESOURCE_PATH;
}

// Given 15, will return a rand nr between 0-14
int getRandomNumber(int range)
{
	srand(time(0)); // This will ensure a really randomized number by help of time.
	return rand()%range; 
}


// Can't use sf::Mouse::isButtonPressed(sf::Mouse::Left) since it is always true. This one resets to false after doing some action
// and is set to true only when left click is pressed again. 
bool leftClickPressed = false;
bool previousLeftClickState = sf::Mouse::isButtonPressed(sf::Mouse::Left);  // Left click on previous refresh. 
double mouseX = 0;		// Mouse coords since sf::Mouse::getPosition(*window).x is too long.
double mouseY = 0;

double relativeMouseX = 0;		// Mouse coords since sf::Mouse::getPosition(*window).x is too long.
double relativeMouseY = 0;


// The size of the whole monitor.
int getMonitorWidth()
{
	static int screen_width = sf::VideoMode::getDesktopMode().width;
	return screen_width;
}
int getMonitorHeight()
{
	static int screen_height = sf::VideoMode::getDesktopMode().height;
	return screen_height;
}
// Returns the size of the programs' window. Can be less or eaqual to monitor size, but never larger. It should be used when creating the window.
int getWindowWidth()
{
	static int windowWidth = 800;

	return windowWidth;
}
int getWindowHeight()
{
	static int windowHeight = 600;

	return windowHeight;
}
sf::Clock runtime;
double SCROLL_SPEED = 10;
bool keys[256];
int mouseScroll = 0; // Negative or positive depending on which way the player scrolls.
sf::RectangleShape mapSize(sf::Vector2f(2000,2000));



