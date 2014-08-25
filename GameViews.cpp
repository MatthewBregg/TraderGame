#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;
#include "CustomizedText.hpp"
#include "regions.hpp"
#include "Texture.hpp"

#include "GameViews.hpp"

// The different parts of the programs' execution.
enum GameView
{
	startMenuView,
	mapView,
};
GameView gameView = mapView;


ButtonSfml charsetSelectButton(300, 400, 150, 150, "Traps", buttonTexture1);
	

void GameViews::init()
{
	initTextures();
}


void GameViews::render(sf::RenderWindow* window)
{
	if (gameView == mapView)										
	{
		charsetSelectButton.draw(window);

		if (charsetSelectButton.isClickedOn())
		{
			window->close();
		}
	}

}
void GameViews::cleanUp()
{

}
