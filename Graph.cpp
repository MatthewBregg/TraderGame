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
// By how much the max value is increased. Needed so that the data does not 
// take up the top part of the graph. I think it looks better that way.
const double MAX_VALUE_INCREASE = 1.3;

Graph::Graph(
	string setName, 
	int setPosX,
	int setPosY
) :
TexturedRectangle(setPosX, setPosY, GRAPH_WIDTH, GRAPH_HEIGHT, genericBg),
name(setName),
initialised(false),
maxValue(20000)
{
}

sf::CircleShape dataPoint(1);
void Graph::draw()
{
	assert(initialised && "Graph should be initialised before being drawn.");

	drawBackground();
	
	// Draw the graph name, centered, on top of the graph.
	double nameWidth = getStringWidth(name, getCustomFont(), TEXT_CHAR_SIZE);
	drawText(name, x + GRAPH_WIDTH / 2.0, y - 25, TEXT_CHAR_SIZE, sf::Color::Black, true);

	// Draw the number on the graphs' left. 
	// If the numbers get longer, they will adjust they position.
	string maxValueInText = strPlusX("", maxValue);
	double maxValueWidth = getStringWidth(maxValueInText, getCustomFont(), TEXT_CHAR_SIZE);
	drawText(maxValueInText, x - maxValueWidth, y - 10);
	
	double zeroStringWidth = getStringWidth("0", getCustomFont(), TEXT_CHAR_SIZE);
	drawText("0", x - zeroStringWidth, y + GRAPH_HEIGHT - 7, TEXT_CHAR_SIZE);

	for (int entity = 0; entity < entities.size(); ++entity)
	{
		dataPoint.setFillColor(colors.at(entity));
		for (int i = 0; i < entities.at(entity).size(); ++i)
		{
			int dataPointPos_x = x + DATA_POINT_X_OFFSET + i * DIST_BETWEEN_POINTS;
			int dataPointPos_y = y - DATA_POINT_Y_OFFSET + GRAPH_HEIGHT - (entities.at(entity).at(i) / maxValue) * DATA_POINT_HEIGHT_SPACE;
			dataPoint.setPosition(dataPointPos_x, dataPointPos_y);
			window->draw(dataPoint);
		}

		// Draws the data point with the entity names besides it. 
		// So players can see which data corresponds to which entity.
		dataPoint.setPosition(int(x + 40), int(y + GRAPH_HEIGHT + 20 + 22 * entity));
		window->draw(dataPoint);
		drawText(names.at(entity), x + 50, y + GRAPH_HEIGHT + 13 + 22 * entity);
	}
}
void Graph::update(unsigned int index, int newValue)
{

  assert(index < entities.size() && "Incorrect index provided.");

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

	return int(newMaxValue * MAX_VALUE_INCREASE);
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
