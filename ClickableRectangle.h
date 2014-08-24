#pragma once


class ClickableRectangle
{
protected:
	double x;
	double y;
	double w;
	double h;

public:
	ClickableRectangle(double setX, double setY, double setW, double setH);

	// Checks if the point is over the rectangle.
	bool isHovering(double pointX, double pointY);
	// Checks if the player has clicked on the button.
	bool isClickedOn();
};