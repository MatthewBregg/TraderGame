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
	void update(double newValue1, double newValue2, double newValue3);
protected:
	int xPos;
	int yPos;
	double maxValue;

	vector<vector<double>> values;
	sf::Sprite background;

};


#endif /* GRAPH_H */
