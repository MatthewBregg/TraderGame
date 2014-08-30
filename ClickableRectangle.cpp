#include "GlobalValues.h"

#include "ClickableRectangle.h"

ClickableRectangle::ClickableRectangle(double setX, double setY, double setW, double setH):
	x(setX),
	y(setY),
	w(setW),
	h(setH)
{

}

// Checks if the point is over the rectangle.
bool ClickableRectangle::isHovering(double pointX, double pointY)
{
	if ((pointX > x) && (pointX < x + w) && 	
		(pointY > y) && (pointY < y + h))     
	{
		return true;
	}
	return false;
}
// Checks if the player has clicked on the button.
bool ClickableRectangle::isClickedOnRelative()
{
	return leftClickPressed && isHovering(relativeMouseX, relativeMouseY);
}

bool ClickableRectangle::isClickedOn()
{
	return leftClickPressed && isHovering(mouseX, mouseY);
}
