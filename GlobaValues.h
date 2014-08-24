#ifndef GLOBAVALUES_H
#define GLOBAVALUES_H




#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>

#include <string>


#include <iostream>
#include <ctime> // Needed for the true randomization
#include <cstdlib> 


#include <SFML/Graphics.hpp>
#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>

#include <string>




#ifdef WIN32 
// Character '\', which is a special formatting character. \\ to fix it
#define RESOURCE_PATH "C:\\Users\\Blue\\Documents\\GitHub\\TraderGame\\"
#endif
#ifdef WIN64
// Character '\', which is a special formatting character. \\ to fix it
const string resourcePath = "C:\\Users\\Blue\\Documents\\GitHub\\TraderGame\\";
#endif
#ifdef __linux__
#define RESOURCE_FOLDER "../"
#endif
#ifdef __APPLE__
#define RESOURCE_FOLDER "Cry me a river, steve"
#endif  
//Shoudln't these paths be local? That way, someone can install this wherever. 
//EX, ../resources
extern string getResourcePath();

// Given 15, will return a rand nr between 0-14
extern int getRandomNumber(int range);


extern sf::Font* getCustomFont();

// Can't use sf::Mouse::isButtonPressed(sf::Mouse::Left) since it is always true. This one resets to false after doing some action
// and is set to true only when left click is pressed again. 
extern bool leftClickPressed;
extern bool previousLeftClickState;  // Left click on previous refresh. 
extern double mouseX;		// Mouse coords since sf::Mouse::getPosition(*window).x is too long.
extern double mouseY;

enum TextureIndex
{
	buttonTexture1,

	totalTextures,
};
extern sf::Texture texturePointer[totalTextures];


extern int getMonitorWidth();
extern int getMonitorHeight();

extern int getWindowWidth();
extern int getWindowHeight();


extern bool keys[256];
extern int mouseScroll; // Negative or positive depending on which way the player scrolls.
#endif /* GLOBAVALUES_H */
