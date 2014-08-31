#include "Texture.h"


#include "TradeCentre.h"


const double TRADE_CENTRE_SIZE = 70;

TradeCentre::TradeCentre(int xPos, int yPos) :
ClickableRectangle(xPos, yPos, TRADE_CENTRE_SIZE, TRADE_CENTRE_SIZE),
isBuilt(true)
{
	tradeCentreSprite.setPosition(xPos, yPos);
	tradeCentreSprite.setTexture(getTexture(tradeCentreTexture));
	tradeCentreSprite.setScale(
		TRADE_CENTRE_SIZE / getTexture(tradeCentreTexture).getSize().x,
		TRADE_CENTRE_SIZE / getTexture(tradeCentreTexture).getSize().y);

}

void TradeCentre::draw()
{
	window->draw(tradeCentreSprite);
}

bool TradeCentre::hasBeenBuilt()
{
	return isBuilt;
}
