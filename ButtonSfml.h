#ifndef BUTTONSFML_H
#define BUTTONSFML_H

#include "GlobalValues.h"

#include "ClickableRectangle.h"
#include "Texture.h"


class ButtonSfml : public TexturedRectangle
{
public:
	ButtonSfml(int setX, int setY, double setW, double setH, string setText, TextureIndex setTexture, int setCharSize = 24);

	void draw();

	void setText(string setText);

	void toggleGrey();
	void setGrey();
	void unsetGrey();
protected:
	TextureIndex textureIndex;
	string text;
	int characterSize;

	sf::Color color;
};

#endif /* BUTTONSFML_H */
