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
	

std::vector<sf::Vector2f> getHexPos()
{
	std::vector<sf::Vector2f> hexPos;
	hexPos.push_back(sf::Vector2f(100,50));
	return hexPos;
}


Region R(getHexPos(), elfFaction, grassLandsHexTexture);
void GameViews::init()
{

}

void GameViews::render(sf::RenderWindow* window)
{
	if (gameView == mapView)										
	{
		charsetSelectButton.draw(window);
		R.draw(*window);

		if (charsetSelectButton.isClickedOn())
		{
			window->close();
		}
	}

}
void GameViews::cleanUp()
{

}
