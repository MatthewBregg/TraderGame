#include "Texture.h"

#include "Graph.h"

const int DIST_BETWEEN_POINTS = 6;
const double GRAPH_WIDTH = 300;
const double GRAPH_HEIGHT = 150;
// Offset so the data points do not start at the very border of the graph.
const double DATA_POINT_X_OFFSET = 5;
const double DATA_POINT_Y_OFFSET = 5;
const int MAX_POINTS = 40; 
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
		drawDataLine(entity);
	}
}

// Used to display the color each enitity uses.
sf::CircleShape entityColorDisplay(1);
void Graph::drawDataLine(int entity)
{
	vector<double>* data = &entities.at(entity);
	vector<sf::Vertex> line;
	line.push_back(sf::Vector2f(x, y + GRAPH_HEIGHT));
	for (int i = 0; i < data->size(); ++i)
	{
		int dataPointPos_x = x + DATA_POINT_X_OFFSET + i * DIST_BETWEEN_POINTS;
		int dataPointPos_y = y - DATA_POINT_Y_OFFSET + GRAPH_HEIGHT - (entities.at(entity).at(i) / maxValue) * GRAPH_HEIGHT;
		
		// 2 points needed to define a line. The first one defines the current line end point.
		// The other defines the next lines start point. This makes the line continuous.
		line.push_back(sf::Vertex(sf::Vector2f(dataPointPos_x, dataPointPos_y), colors.at(entity)));
		line.push_back(sf::Vertex(sf::Vector2f(dataPointPos_x, dataPointPos_y), colors.at(entity)));
	}

	/*   // A cool bug.
	int dataPointPos_x = x + DATA_POINT_X_OFFSET + i * DIST_BETWEEN_POINTS;
	int dataPointPos_y = y - DATA_POINT_Y_OFFSET + GRAPH_HEIGHT - (entities.at(entity).at(i) / maxValue) * GRAPH_HEIGHT;

	// 2 points needed to define a line. Take the previous one so that the data line is continuous.
	if (i > 0)
	{
	line.push_back(line.at(i - 1));
	}
	line.push_back(sf::Vector2f(dataPointPos_x, dataPointPos_y));

	*/

	// Draws the data point with the entity names besides it. 
	// So players can see which data corresponds to which entity.
	entityColorDisplay.setFillColor(colors.at(entity));
	entityColorDisplay.setPosition(int(x + 40), int(y + GRAPH_HEIGHT + 20 + 22 * entity));
	window->draw(entityColorDisplay);
	drawText(names.at(entity), x + 50, y + GRAPH_HEIGHT + 13 + 22 * entity);

	if (data->size() > 0)
	{
		window->draw(&line[0], line.size(), sf::Lines);
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
