#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;
#include "Regions.hpp"
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


void GameViews::init()
{

}

void GameViews::render()
{
	if (gameView == mapView)										
	{
		R.draw();
		EndTurn::draw();
		EndTurn::refresh();
	}
}
void GameViews::cleanUp()
{

}
