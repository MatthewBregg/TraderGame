


#include "GlobalValues.h"


sf::RenderWindow* window;
sf::View* view;

sf::View* DEFAULT_VIEW;

string getResourcePath()
{
	return RESOURCE_PATH;
}

void initRandom()
{
	srand(time(0)); // This will ensure a really randomized number by help of time.
}
// Given 15, will return a rand nr between 0-14
int getRandomNumber(int range)
{
	static bool randNotInitialised = false;
	if (randNotInitialised)
	{
		initRandom();
	}
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
    return getAndUpdateWindowWidth(false);
}
int getAndUpdateWindowWidth(bool update)
{
	static int windowWidth = 900;
	if (update)
	    {
		windowWidth = window->getSize().x;
	    }

	return windowWidth;
}
int getAndUpdateWindowHeight(bool update)
{
	static int windowHeight = 676;
	if(update)
	    {
		windowHeight = window->getSize().y;
	    }
	return windowHeight;
}

int getWindowHeight()
{
    return getAndUpdateWindowHeight(false);
}
sf::Clock runtime;
double SCROLL_SPEED = 2;
bool keys[256];
int mouseScroll = 0; // Negative or positive depending on which way the player scrolls.

sf::RectangleShape mapSize(sf::Vector2f(2000,2000));



// A drawing method that anyone can use. Used when the caller does not want to deal
// with the sprite crap on his side. 
sf::Sprite freeSprite;
void drawSprite(int x, int y, double w, double h, TextureIndex textureIndex)
{
	freeSprite.setPosition(x, y);
	freeSprite.setTexture(getTexture(textureIndex));
	freeSprite.setScale(w / getTexture(textureIndex).getSize().x, h / getTexture(textureIndex).getSize().y);
	window->draw(freeSprite);
}
	
