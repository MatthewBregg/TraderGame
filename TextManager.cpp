
#include "Regions.h"
#include "ButtonSfml.h"


#include "TextManager.h"


const sf::Font& getCustomFont()
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
	return font;
}

// Returns the pixel width of the given string, if it was drawn on the screen. 
// Can be used for centering text. 
double getStringWidth(string givenString, const sf::Font& font, int characterSize)
{
	sf::Text temp(givenString, font, characterSize);

	double stringWidth = 0; 
	for (unsigned int i = 0; i < temp.getString().getSize(); ++i)
	{
		stringWidth += font.getGlyph(temp.getString()[i], characterSize, false).advance;
	}
	return stringWidth;
}

// A method for drawing text without having to create text object on your own. 
sf::Text freeText;
void drawText(string text, int x, int y, int characterSize, sf::Color color, bool centered)
{
	freeText.setString(text);
	if (centered)
	{
		freeText.setPosition(x - getStringWidth(text, getCustomFont(), characterSize) / 2.0, y);
	}
	else
	{
		freeText.setPosition(x, y);
	}
	freeText.setCharacterSize(characterSize);
	freeText.setColor(color);

	freeText.setFont(getCustomFont());
	window->draw(freeText);
}

