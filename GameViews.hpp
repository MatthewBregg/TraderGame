#ifndef GAMEVIEWS_H
#define GAMEVIEWS_H



#include "ButtonSfml.hpp"
#include "GlobalValues.hpp"



class GameViews
{
public:

	static void init();
	static void render(sf::RenderWindow* window);

	static void cleanUp();


};

#endif /* GAMEVIEWS_H */
