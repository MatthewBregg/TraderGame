#ifndef CUSTOMIZEDTEXT_H
#define CUSTOMIZEDTEXT_H





#include <vector>	
#include <iostream>			//File output un input
#include <fstream>    // fstream provides an interface to read and write data from files as input/output streams.
#include <sstream>
#include <array>
#include <string>
using namespace std;

#include "GlobalValues.hpp"

class CustomizedText: public sf::Text
{
public:
	void init(string setString, int charSize, int posX, int posY, sf::Font* font = NULL);
};
#endif /* CUSTOMIZEDTEXT_H */
