
#include "Regions.h"
#include "ButtonSfml.h"


#include "EndTurn.h"

ButtonSfml endTurnButton(0, 0, 100, 100, "End turn", genericBg);

void EndTurn::draw()
{
	endTurnButton.setPos(getWindowWidth() - 130, getWindowHeight() - 130);
	endTurnButton.draw();
}
bool EndTurn::handleInput()
{
	if (endTurnButton.isClickedOn())
	{
		EndTurn::endTurn();
		return true;
	}
	if (keys[57])   // Press space to fastforward.
	{
		EndTurn::endTurn();
	}

	return false;
}

void EndTurn::endTurn()
{

	world.updateAfterTurn();
}
