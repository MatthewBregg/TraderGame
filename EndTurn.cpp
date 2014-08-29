
#include "Regions.hpp"
#include "ButtonSfml.hpp"


#include "EndTurn.hpp"

ButtonSfml EndTurnButton(getWindowWidth() - 150, getWindowHeight() - 150, 130, 130, "End turn", buttonTexture1);

void EndTurn::draw()
{
	EndTurnButton.draw();
}
void EndTurn::refresh()
{
	if (EndTurnButton.isClickedOn())
	{
		EndTurn::endTurn();
	}
}

void EndTurn::endTurn()
{

	M.updateAfterTurn();
}
