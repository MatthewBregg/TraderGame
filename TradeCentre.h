#include "Resources.h"
#include "GlobalValues.h"
#include "ClickableRectangle.h"

#ifndef TRADECENTRE_H
#define TRADECENTRE_H


class TradeCentre : public ClickableRectangle
{
public:
	TradeCentre(int xPos, int yPos);

	void draw();
	bool hasBeenBuilt();
private:
	bool isBuilt;
	sf::Sprite tradeCentreSprite;

};


#endif /* TRADECENTRE_H */
