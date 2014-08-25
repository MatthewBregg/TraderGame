#include <iostream>
#include "GlobalValues.hpp"


#include "Texture.hpp"


sf::Texture* getTexture(TextureIndex textureIndex)
{
	static sf::Texture texturePointer[totalTextures];	

	if (texturePointer[textureIndex].getSize().x == 0 && texturePointer[textureIndex].getSize().y == 0)
	{
		if (!texturePointer[buttonTexture1].loadFromFile(getResourcePath() + "buttonNext.png"))	{		/*// error...#*/	}
		if (!texturePointer[grassLandsHexTexture].loadFromFile(getResourcePath() + "grasslandsHex.png"))	{		/*// error...#*/	}
	}
	return &texturePointer[textureIndex];
}
