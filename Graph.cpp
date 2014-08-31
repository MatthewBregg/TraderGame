#include "Texture.h"

#include "Graph.h"


const int DIST_BETWEEN_POINTS = 6;
const double GRAPH_WIDTH = 200;
const double GRAPH_HEIGHT = 100;
// How much space can the data point occupy. 
// Needed so that they do not overlap with the graph borders.
const double DATA_POINT_HEIGHT_SPACE = 86;
// Offset so the data points do not start at the very border of the graph.
const double DATA_POINT_X_OFFSET = 6;
const double DATA_POINT_Y_OFFSET = 6;
const int MAX_POINTS = 32; 
const int TEXT_CHAR_SIZE = 14;

Graph::Graph(string setName, int setX, int setY) :
name(setName),
initialised(false),
xPos(setX),
yPos(setY),
maxValue(20000)
{
	background.setPosition(xPos, yPos);
	background.setTexture(getTexture(randomBg));
	background.setScale(GRAPH_WIDTH / getTexture(randomBg).getSize().x, GRAPH_HEIGHT / getTexture(randomBg).getSize().y);
}

sf::CircleShape dataPoint(1);
void Graph::draw()
{
	assert(initialised && "Graph should be initialised before being drawn.");

	window->draw(background);
	
	// Draw the graph name, centered, on top of the graph.
	double nameWidth = getStringWidth(name, getCustomFont(), TEXT_CHAR_SIZE);
	drawText(name, xPos + GRAPH_WIDTH / 2.0 - nameWidth / 2.0, yPos - 25);

	// Draw the number on the graphs' left. 
	// If the numbers get longer, they will adjust they position.
	string maxValueInText = strPlusX("", maxValue);
	double maxValueWidth = getStringWidth(maxValueInText, getCustomFont(), TEXT_CHAR_SIZE);
	drawText(maxValueInText, xPos - maxValueWidth, yPos - 10);
	
	double zeroStringWidth = getStringWidth("0", getCustomFont(), TEXT_CHAR_SIZE);
	drawText("0", xPos - zeroStringWidth, yPos + GRAPH_HEIGHT - 7, TEXT_CHAR_SIZE);

	for (int entity = 0; entity < entities.size(); ++entity)
	{
		dataPoint.setFillColor(colors.at(entity));
		for (int i = 0; i < entities.at(entity).size(); ++i)
		{
			int dataPointPos_x = xPos + DATA_POINT_X_OFFSET + i * DIST_BETWEEN_POINTS;
			int dataPointPos_y = yPos - DATA_POINT_Y_OFFSET + GRAPH_HEIGHT - (entities.at(entity).at(i) / maxValue) * DATA_POINT_HEIGHT_SPACE;
			dataPoint.setPosition(dataPointPos_x, dataPointPos_y);
			window->draw(dataPoint);
		}

		// Draws the data point with the entity names besides it. 
		// So players can see which data corresponds to which entity.
		dataPoint.setPosition(int(xPos + 40), int(yPos + GRAPH_HEIGHT + 20 + 22 * entity));
		window->draw(dataPoint);
		drawText(names.at(entity), xPos + 50, yPos + GRAPH_HEIGHT + 13 + 22 * entity);
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

	maxValue = findMaxValue(); 
}

// Goes through all the values to find the largest one and return it.
double Graph::findMaxValue()
{
	double newMaxValue = 1;

	for (auto& entity : entities)
	{
		for (auto& value : entity)
		{
			if (value > newMaxValue)
			{
				newMaxValue = value;
			}
		}
	}

	return newMaxValue;
}

void Graph::initialise(int numberOfEntities, vector<sf::Color> setColors, vector<string> setNames)
{
	vector<double> temp;
	for (int i = 0; i < numberOfEntities; ++i)
	{
		entities.push_back(temp);
	}
	colors = setColors;
	names = setNames;

	initialised = true;
}