
#include "Regions.hpp"
#include "ButtonSfml.hpp"


#include "EndTurn.hpp"

ButtonSfml EndTurnButton(getWindowWidth() - 200, getWindowHeight() - 200, 150, 150, "End turn", buttonTexture1);

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
