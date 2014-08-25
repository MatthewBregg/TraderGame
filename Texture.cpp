#include <iostream>
#include "GlobalValues.hpp"


#include "Texture.hpp"

static sf::Texture texturePointer[totalTextures];	 
void initTextures()
{
	if (!texturePointer[buttonTexture1].loadFromFile(getResourcePath() + "buttonNext.png"))	{		/*// error...#*/	}
	if (!texturePointer[grassLandsHexTexture].loadFromFile(getResourcePath() + "grasslandsHex.png"))	{		/*// error...#*/	}

	
}

sf::Texture* getTexture(TextureIndex textureIndex)
{
	if (texturePointer[textureIndex].getSize().x == 0 && texturePointer[textureIndex].getSize().y == 0)
	{
		initTextures();
	}
	return &texturePointer[textureIndex];
}
