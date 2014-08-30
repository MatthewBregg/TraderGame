#include <iostream>
#include <vector>
#include "GlobalValues.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
	Graph(int setX, int setY);
	void draw();
	void update(unsigned int index, int newValue);

	void initialise(int numberOfEntities, vector<sf::Color> setColors);
protected:
	bool initialised;
	int xPos;
	int yPos;
	double maxValue;

	vector<vector<double>> entities;
	vector<sf::Color> colors;
	sf::Sprite background;

};


#endif /* GRAPH_H */
