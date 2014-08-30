#include "Texture.h"


#include "Graph.h"

Graph::Graph(int setX, int setY):
xPos(setX),
yPos(setY),
maxValue(0)
{
	vector<double> temp;
	values.push_back(temp);
	values.push_back(temp);
	values.push_back(temp);

	background.setPosition(xPos, yPos);
	background.setTexture(getTexture(buttonTexture1));
	background.setScale(200.0 / getTexture(buttonTexture1).getSize().x, 100.0 / getTexture(buttonTexture1).getSize().y);
}

sf::CircleShape dataPoint(1);
const int DIST_BETWEEN_POINTS = 10;
const int MAX_POINTS = 20;
void Graph::draw()
{
	window->draw(background);
	
	drawText(strPlusX("", maxValue), xPos - 50, yPos - 10);

	int counter = 0;
	for (int i = 0; i < values.at(0).size(); ++i)
	{
		dataPoint.setFillColor(sf::Color::Green);
		dataPoint.setPosition(xPos + counter * DIST_BETWEEN_POINTS, yPos + 100 - (values.at(0).at(i) / maxValue) * 100);
		window->draw(dataPoint);

		dataPoint.setFillColor(sf::Color::Red);
		dataPoint.setPosition(xPos + counter * DIST_BETWEEN_POINTS, yPos + 100 - (values.at(1).at(i) / maxValue) * 100);
		window->draw(dataPoint);

		dataPoint.setFillColor(sf::Color::Blue);
		dataPoint.setPosition(xPos + counter * DIST_BETWEEN_POINTS, yPos + 100 - (values.at(2).at(i) / maxValue) * 100);
		window->draw(dataPoint);
		counter++;
	}
}
void Graph::update(double newValue1, double newValue2, double newValue3)
{
	values.at(0).push_back(newValue1);
	values.at(1).push_back(newValue2);
	values.at(2).push_back(newValue3);


	if (newValue1 > maxValue)
	{
		maxValue = newValue1;
	}
	if (newValue2 > maxValue)
	{
		maxValue = newValue2;
	}	
	if (newValue3 > maxValue)
	{
		maxValue = newValue3;
	}
	if (values.at(0).size() > MAX_POINTS)  
	{
		// Remove the oldest value.
		values.at(0).erase(values.at(0).begin());
		values.at(1).erase(values.at(1).begin());
		values.at(2).erase(values.at(2).begin());
	}
}

