#include "ButtonSfml.hpp"


ButtonSfml::ButtonSfml(double setX, double setY, double setW, double setH, string setText, TextureIndex setTexture):
	ClickableRectangle(setX, setY, setW, setH),
	textureIndex(setTexture)
{
	sprite.setPosition(setX, setY);
	sprite.setTexture(*getTexture(textureIndex));
	sprite.setScale(w / getTexture(textureIndex)->getSize().x, h/ getTexture(textureIndex)->getSize().y);
	
	buttonText.setFont(*getCustomFont()); 
	buttonText.setCharacterSize(30); 
	buttonText.setString(setText);
	buttonText.setPosition(sprite.getPosition());
}

void ButtonSfml::draw()
{
	double textWidth = 0; // Width of the string in text, used for centering the text on the buttons.
	for (int i = 0; i < buttonText.getString().getSize(); ++i)
	{
		if (buttonText.getString()[i] != 10) // To deal with empty characters at the end of some text converted from wchar_t.
		{
			textWidth += buttonText.getFont()->getGlyph(buttonText.getString()[i], buttonText.getCharacterSize(), false).advance;
		}
	}
	
	string t = buttonText.getString();
		buttonText.setPosition(int(sprite.getPosition().x + w/2 - (textWidth/2)),  int(sprite.getPosition().y + h/3));
	window->draw(sprite);
	window->draw(buttonText);
}

void ButtonSfml::setText(string setText)
{
	buttonText.setString(setText);
}
void ButtonSfml::setText(wstring setText)
{
	buttonText.setString(setText);
}
void ButtonSfml::setPoz(double newX, double newY)
{
	x = newX;
	y = newY;

	sprite.setPosition(x, y);
	buttonText.setPosition(sprite.getPosition());
}
