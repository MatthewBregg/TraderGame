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
		int setOffsetY,
		bool setIfIntegerValues
	);

	void draw();
	void update(unsigned int index, double newValue);
	
	// Goes through all the values to find the largest one and return it.
	double findMaxValue();
	void initialise(int numberOfEntities, vector<sf::Color> setColors, vector<string> setNames);
protected:
	string name;
	bool initialised;
	double maxValue;
	// If the data displayed in the graph are integers. Needed to fix rounding errors.
	bool integerValues;  

	vector<vector<double>> entities;
	vector<sf::Color> colors;
	vector<string> names; 

	void drawDataLine(int entity);
};


#endif /* GRAPH_H */
