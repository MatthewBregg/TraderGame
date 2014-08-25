#include "CustomizedText.hpp"


#include "City.hpp"



 City::City(Resources r, int g):
	resources(r),
	gold(g),
	population(10000)
 {
 	populationText.setFont(*getCustomFont()); 
	populationText.setCharacterSize(16); 
	populationText.setPosition(200, 200);
 };

void City::draw(double x, double y)
{
	stringstream cityPopulation;	cityPopulation << "Population: " << population;
	populationText.setString(cityPopulation.str());
	populationText.setPosition(x, y);
	window->draw(populationText);
	
	stringstream cityPopulationChange;	cityPopulationChange << "Population change: " << getPopulationChange();
	populationText.setString(cityPopulationChange.str());
	populationText.setPosition(x + 170, y);
	window->draw(populationText);
	

	stringstream foodInStock;	foodInStock << "Food in stock: " << resources.getFood();
	populationText.setString(foodInStock.str());
	populationText.setPosition(x, y + 30);
	window->draw(populationText);

	stringstream foodRequirement;	foodRequirement << "Food required: " << getPopulationFoodReq();  
	populationText.setString(foodRequirement.str());
	populationText.setPosition(x + 170, y + 30);
	window->draw(populationText);
}
void City::refreshAfterTurn()
{
	updatePopulation();
}

void City::updatePopulation()
{
	resources.subtractFood(getPopulationFoodReq());
	population *= getPopulationChange();
}


unsigned int City::getPopulationFoodReq()
{
	return ceil(double(population)/2000.0);
}
double City::getPopulationChange()
{
	if (resources.getFood() == 0)		// Nothing to eat.
	{
		return 0.7;	// Litte food, population plummets.
	}
	else if (resources.getFood() >= getPopulationFoodReq())
	{
		return 1.1;	// Lots of food, population increases.
	}
	else if (resources.getFood() >= getPopulationFoodReq() * 0.8)
	{
		return  1;	 // Stays the same.
	}
	else 
	{
		return 0.9;		// Litte food, population decreases.
	}
}