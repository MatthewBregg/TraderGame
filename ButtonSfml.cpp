#include "ButtonSfml.h"


ButtonSfml::ButtonSfml(int setX, int setY, double setW, double setH, string setText, TextureIndex setTexture, int setCharSize
) :
TexturedRectangle(setX, setY, setW, setH, setTexture),
textureIndex(setTexture),
text(setText),
characterSize(setCharSize),
color(background.getColor())
{

}

void ButtonSfml::draw()
{
	window->draw(background);
	
	// *0.6 Centers the text a bit better vertically.
	drawText(text, x + w / 2.0, y + h / 2.0 - characterSize*0.6, characterSize, sf::Color::Black, true);
}

void ButtonSfml::setText(string setText)
{
	text = setText;
}

void ButtonSfml::toggleGrey()
{
    if (background.getColor() == color)
	{
		background.setColor(sf::Color(50, 50, 50, 128)); // Mess with these values to control how a 'greyed out' sprite looks.
	}
    else
	{
		background.setColor(color);
	}
}
void ButtonSfml::setGrey()
{
	background.setColor(sf::Color(50, 50, 50, 128)); //Mess with these values to control how a 'greyed out' sprite looks.
}
void ButtonSfml::unsetGrey()
{
	background.setColor(color);
}
