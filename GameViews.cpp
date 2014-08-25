#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;
#include "regions.hpp"
#include "Texture.hpp"
#include "EndTurn.hpp"

#include "GameViews.hpp"

// The different parts of the programs' execution.
enum GameView
{
	startMenuView,
	mapView,
};
GameView gameView = mapView;


ButtonSfml EndTurnButton(300, 400, 150, 150, "End turn", buttonTexture1);
	
void GameViews::init()
{

}

void GameViews::render()
{
	if (gameView == mapView)										
	{
		EndTurnButton.draw();
		R.draw();

		if (EndTurnButton.isClickedOn())
		{
			EndTurn::endTurn();
		}
	}

}
void GameViews::cleanUp()
{

}
