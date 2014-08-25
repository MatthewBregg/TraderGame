#include "GlobalValues.hpp"


sf::RenderWindow* window;

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

sf::Font* getCustomFont()
{
	static bool fontInitialised = false;
	static sf::Font font;
	if (fontInitialised == false)
	{
		string filename = getResourcePath() + "mplus-1p-medium.ttf";
		if (!font.loadFromFile(filename)){	/*error**/ }
		else {
			fontInitialised = true;
		}
	}
	return &font;
}

// Can't use sf::Mouse::isButtonPressed(sf::Mouse::Left) since it is always true. This one resets to false after doing some action
// and is set to true only when left click is pressed again. 
extern bool leftClickPressed = false;
extern bool previousLeftClickState = sf::Mouse::isButtonPressed(sf::Mouse::Left);  // Left click on previous refresh. 
extern double mouseX = 0;		// Mouse coords since sf::Mouse::getPosition(*window).x is too long.
extern double mouseY = 0;



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


bool keys[256];
int mouseScroll = 0; // Negative or positive depending on which way the player scrolls.


sf::Text freeText;
// Some methods for drawing text without having to create text objects on their side. 
void drawText(string text, double x, double y)
{
	freeText.setFont(*getCustomFont()); 
	freeText.setCharacterSize(14); 
	freeText.setString(text);
	freeText.setPosition(x, y);
	window->draw(freeText);
}



