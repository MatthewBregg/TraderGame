#ifndef CLICKABLERECTANGLE_H
#define CLICKABLERECTANGLE_H

#include "GlobalValues.h"
#include "Texture.h"

class ClickableRectangle
{

public:
	ClickableRectangle(double setX, double setY, double setW, double setH);

	// Checks if the point is over the rectangle.
	bool isHovering(double pointX, double pointY);
	bool isMouseHovering();

	// Checks if the player has clicked on the button.
	bool isClickedOn();
	bool isClickedOnRelative();

	virtual void setPos(double newX, double newY);
	sf::Vector2<double> getPos() const;

protected:
	double x;
	double y;
	double w;
	double h;

};

class TexturedRectangle : public ClickableRectangle
{
public:
	TexturedRectangle(double setX, double setY, double setW, double setH, TextureIndex setTexture);

	void drawBackground();

	virtual void setPos(double newX, double newY);
protected:


	sf::Sprite background;

};



#endif /* CLICKABLERECTANGLE_H */
