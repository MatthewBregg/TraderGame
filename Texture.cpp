#include <iostream>
#include "GlobalValues.hpp"


#include "Texture.hpp"


sf::Texture texturePointer[totalTextures];

void initTextures()
{
	if (!texturePointer[buttonTexture1].loadFromFile(getResourcePath() + "buttonNext.png"))	{		/*// error...#*/	}


}
