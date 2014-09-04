#include <iostream>
#ifndef FONTMANAGER_H
#define FONTMANAGER_H


// A collection of various functions for handling text.


extern const sf::Font& getCustomFont();

// Returns the pixel width of the given string, if it was drawn on the screen. 
// Can be used for centering text. 
extern double getStringWidth(string givenString, const sf::Font& font, int characterSize);

// A method for drawing text without having to create text object on your own. 
extern void drawText(string text, int x, int y, int characterSize = 14, sf::Color color = sf::Color::Black, bool centered = false);

template <typename SOME_VALUE>
// Methods for adding string and some value together, be it a string or a number or 
// whatever. As long as stringstream supports it. 
string strPlusX(string text, SOME_VALUE value)
{
	stringstream textString;	textString << text << value;
	return textString.str();
}


#endif /* FONTMANAGER_H */
