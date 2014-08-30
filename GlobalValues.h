#ifndef GlobalValues_H
#define GlobalValues_H




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


extern sf::RenderWindow* window;
extern sf::View* view;

// Defines the resource folder path. Debug has different paths, as the exes might
// be generated to different folders. 
// In the release version, though, the exe should always be one folder above the
// "Resources" folder.
#ifdef _DEBUG  // If running in debug.
	#ifdef _WIN32			 // Defined for both 32-bit and 64-bit environments 
		// Character '\', which is a special formatting character. \\ to fix it
		#define RESOURCE_PATH "C:\\Users\\Blue\\Documents\\GitHub\\TraderGame\\Resources\\"
	#endif
	#ifdef __linux__
		#define RESOURCE_PATH "../Resources/"
	#endif
	#ifdef __APPLE__
		#define RESOURCE_PATH "../Resources/" //Should work fine for osx also
	#endif  
#endif
#ifndef _DEBUG  // Running in release, define a relative resource folder path.
	#ifdef _WIN32			 // Defined for both 32-bit and 64-bit environments 
		// Character '\', which is a special formatting character. \\ to fix it
		#define RESOURCE_PATH "Resources\\"
	#endif
	#ifdef __linux__
		#define RESOURCE_PATH "../Resources/"
	#endif
	#ifdef __APPLE__
		#define RESOURCE_PATH "../Resources/" //Should work fine for osx also
	#endif  
#endif


extern string getResourcePath();

// Given 15, will return a rand nr between 0-14
extern int getRandomNumber(int range);
extern double SCROLL_SPEED;
extern sf::Clock runtime;

extern sf::RectangleShape mapSize;

extern sf::Font* getCustomFont();

// sf::Mouse::isButtonPressed(sf::Mouse::Left) since it is always true while the click is down. 
// (Meaning buttons will get clicked 20 times per sec. leftClickPressed resets to false after 1 
// refresh and is set to true only when left click is released and pressed again. 
extern bool leftClickPressed;
extern bool previousLeftClickState;  // Left click on previous refresh. 
extern double mouseX;		// Mouse coords since sf::Mouse::getPosition(*window).x is too long.
extern double mouseY;


extern int getMonitorWidth();
extern int getMonitorHeight();

extern int getWindowWidth();
extern int getWindowHeight();


extern bool keys[256];
extern int mouseScroll; // Negative or positive depending on which way the player scrolls.


// Some methods for drawing text like this "something: x".
extern void drawText(string text, int x, int y);

template <typename SOME_VALUE>
// Methods for adding string and some value together, be it a string or a number or 
// whatever. As long as stringstream supports it. 
string strPlusX(string text, SOME_VALUE value)
{
	stringstream textString;	textString << text << value;
	return textString.str();
}



#endif /* GlobalValues_H */
