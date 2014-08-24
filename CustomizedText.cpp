#include "CustomizedText.hpp"



void CustomizedText::init(string setString, int charSize, int posX, int posY, sf::Font* font)
{
	if (font == NULL)  // If font has not been provided.
	{
		setFont(*getCustomFont()); 
	}
	else
	{
		setFont(*font); 
	}
	setCharacterSize(charSize); 
	setPosition(posX, posY);
	this->setString(setString);
}
