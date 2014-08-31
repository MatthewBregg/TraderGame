#ifndef BUTTONSFML_H
#define BUTTONSFML_H

#include "GlobalValues.h"

#include "ClickableRectangle.h"
#include "Texture.h"


class ButtonSfml: public ClickableRectangle
{
public:
	ButtonSfml(double setX, double setY, double setW, double setH, string setText, TextureIndex setTexture);

	void draw();

	void setText(string setText);

	void setPoz(double newX, double newY);
protected:
	TextureIndex textureIndex;

	sf::Sprite button;
	sf::Text buttonText;
};

#endif /* BUTTONSFML_H */
