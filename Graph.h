#include <iostream>
#include <vector>
#include "GlobalValues.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
	Graph(string setName, int setX, int setY);
	void draw();
	void update(unsigned int index, int newValue);
	
	// Goes through all the values to find the largest one and return it.
	double findMaxValue();
	void initialise(int numberOfEntities, vector<sf::Color> setColors, vector<string> setNames);
protected:
	string name;
	bool initialised;
	int xPos;
	int yPos;
	double maxValue;

	vector<vector<double>> entities;
	vector<sf::Color> colors;
	vector<string> names; 

	sf::Sprite background;

};


#endif /* GRAPH_H */
