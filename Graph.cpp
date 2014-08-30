#include "Texture.h"
#include <assert.h>


#include "Graph.h"

Graph::Graph(int setX, int setY) :
initialised(false),
xPos(setX),
yPos(setY),
maxValue(0)
{
	background.setPosition(xPos, yPos);
	background.setTexture(getTexture(buttonTexture1));
	background.setScale(200.0 / getTexture(buttonTexture1).getSize().x, 100.0 / getTexture(buttonTexture1).getSize().y);
}

sf::CircleShape dataPoint(1);
const int DIST_BETWEEN_POINTS = 10;
const int MAX_POINTS = 20;
void Graph::draw()
{
	assert(initialised && "Graph should be initialised before being drawn.");

	window->draw(background);
	
	drawText(strPlusX("", maxValue), xPos - 50, yPos - 10);

	for (int entity = 0; entity < entities.size(); ++entity)
	{
		for (int i = 0; i < entities.at(entity).size(); ++i)
		{
			dataPoint.setFillColor(colors.at(entity));
			dataPoint.setPosition(int(xPos + i * DIST_BETWEEN_POINTS), int(yPos + 100 - (entities.at(entity).at(i) / maxValue) * 100));
			window->draw(dataPoint);
		}
	}
}
void Graph::update(unsigned int index, int newValue)
{
	assert(index < entities.size());

	vector<double>* entity = &entities.at(index);
	entity->push_back(newValue);

	if (newValue > maxValue)
	{
		maxValue = newValue;
	}

	if (entity->size() > MAX_POINTS)
	{
		// Remove the oldest value.
		entity->erase(entity->begin());
	}
}

void Graph::initialise(int numberOfEntities, vector<sf::Color> setColors)
{
	vector<double> temp;
	for (int i = 0; i < numberOfEntities; ++i)
	{
		entities.push_back(temp);
	}
	colors = setColors;

	initialised = true;
}