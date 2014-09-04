#include "ButtonSfml.h"


ButtonSfml::ButtonSfml(double setX, double setY, double setW, double setH, string setText, TextureIndex setTexture, int setCharSize):
	ClickableRectangle(setX, setY, setW, setH),
	textureIndex(setTexture),
	text(setText),
	characterSize(setCharSize),
	color(button.getColor())
{
	button.setPosition(setX, setY);
	button.setTexture(getTexture(textureIndex));
	button.setScale(w / getTexture(textureIndex).getSize().x, h / getTexture(textureIndex).getSize().y);
}

void ButtonSfml::draw()
{
	window->draw(button);
	
	// *0.6 Centers the text a bit better vertically.
	drawText(text, 
		button.getPosition().x + w / 2.0, 
		button.getPosition().y + h / 2.0 - characterSize*0.6, characterSize, sf::Color::Black, true);
}

void ButtonSfml::setText(string setText)
{
	text = setText;
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
		button.setColor(sf::Color(50,50,50,128)); // Mess with these values to control how a 'greyed out' sprite looks.
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
