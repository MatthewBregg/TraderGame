#include "ButtonSfml.h"


ButtonSfml::ButtonSfml(double setX, double setY, double setW, double setH, string setText, TextureIndex setTexture, int setCharSize):
	ClickableRectangle(setX, setY, setW, setH),
	textureIndex(setTexture),
	characterSize(setCharSize),
	color(button.getColor())
{
	button.setPosition(setX, setY);
	button.setTexture(getTexture(textureIndex));
	button.setScale(w / getTexture(textureIndex).getSize().x, h / getTexture(textureIndex).getSize().y);
	
	buttonText.setFont(getCustomFont()); 
	buttonText.setCharacterSize(setCharSize);
	buttonText.setString(setText);
	buttonText.setPosition(button.getPosition());

}

void ButtonSfml::draw()
{
	window->draw(button);

	// Width of the string in text, used for centering the text on the buttons.
	double textWidth = getStringWidth(buttonText.getString(), *(buttonText.getFont()), buttonText.getCharacterSize());
	buttonText.setPosition(int(button.getPosition().x + w / 2 - (textWidth / 2)), int(button.getPosition().y + h / 2.0 - characterSize/1.5));

	window->draw(buttonText);
}

void ButtonSfml::setText(string setText)
{
	buttonText.setString(setText);
}
void ButtonSfml::setPos(double newX, double newY)
{
	x = newX;
	y = newY;

	button.setPosition(x, y);
}
void ButtonSfml::toggleGrey()
{
    if (button.getColor() == color)
	{
	
	button.setColor(sf::Color(50,50,50,128)); //Mess with these values to control how a 'greyed out' sprite looks.

	}
    else
	{
	    button.setColor(color);
	}
}
void ButtonSfml::setGrey()
{
    button.setColor(sf::Color(50,50,50,128)); //Mess with these values to control how a 'greyed out' sprite looks.
}
void ButtonSfml::unsetGrey()
{
    button.setColor(color);
}
