#include "CustomizedText.hpp"



#include "City.hpp"



 City::City(Resources r, int g):
 resources(r),
	 gold(g),
	 population(10000)
 {

 	populationText.setFont(*getCustomFont()); 
	populationText.setCharacterSize(30); 
	populationText.setPosition(200, 200);
 };

void City::draw(sf::RenderWindow& window)
{
	stringstream stream1;
	stream1 << population;
	populationText.setString(stream1.str());
	window.draw(populationText);
}
void City::refreshAfterTurn()
{
	population -= 200;
}
