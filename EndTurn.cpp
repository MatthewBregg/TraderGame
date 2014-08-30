
#include "Regions.hpp"
#include "ButtonSfml.hpp"


#include "EndTurn.hpp"

ButtonSfml EndTurnButton(getWindowWidth() - 150, getWindowHeight() - 150, 130, 130, "End turn", buttonTexture1);

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
