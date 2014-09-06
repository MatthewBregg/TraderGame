#include "GlobalValues.h"
#include "ClickableRectangle.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph : public TexturedRectangle
{
public:
	Graph(
		string setName, 
		int setOffsetX,
		int setOffsetY
	);

	void draw();
	void update(unsigned int index, int newValue);
	
	// Goes through all the values to find the largest one and return it.
	double findMaxValue();
	void initialise(int numberOfEntities, vector<sf::Color> setColors, vector<string> setNames);
protected:
	string name;
	bool initialised;
	double maxValue;

	vector<vector<double>> entities;
	vector<sf::Color> colors;
	vector<string> names; 
};


#endif /* GRAPH_H */
