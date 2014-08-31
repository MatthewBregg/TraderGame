
#include "Regions.h"
#include "ButtonSfml.h"


#include "EndTurn.h"

ButtonSfml EndTurnButton(getWindowWidth() - 150, getWindowHeight() - 150, 130, 130, "End turn", randomBg);

void EndTurn::draw()
{
	EndTurnButton.draw();
}
bool EndTurn::handleInput()
{
	if (EndTurnButton.isClickedOn())
	{
		EndTurn::endTurn();
		return true;
	}
	return false;
}

void EndTurn::endTurn()
{

	world.updateAfterTurn();
}
