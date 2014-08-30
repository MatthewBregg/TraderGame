#ifndef BUTTONSFML_H
#define BUTTONSFML_H

#include "GlobalValues.h"

#include "ClickableRectangle.h"
#include "Texture.h"


class ButtonSfml: public ClickableRectangle
{
	TextureIndex textureIndex;
	
	sf::Text buttonText;
	sf::Sprite sprite;
public:
	ButtonSfml(double setX, double setY, double setW, double setH, string setText, TextureIndex setTexture);

	void draw();

	void setText(string setText);
	void setText(wstring setText);

	void setPoz(double newX, double newY);
};

#endif /* BUTTONSFML_H */
