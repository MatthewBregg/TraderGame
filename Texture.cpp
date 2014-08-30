#include <iostream>
#include "GlobalValues.hpp"


#include "Texture.hpp"


const sf::Texture& getTexture(TextureIndex textureIndex)
{
	static sf::Texture texturePointer[totalTextures];	

	if (texturePointer[textureIndex].getSize().x == 0 && texturePointer[textureIndex].getSize().y == 0)
	{
		if (!texturePointer[buttonTexture1].loadFromFile(getResourcePath() + "buttonNext.png")			|| 
			!texturePointer[grassLandsHex].loadFromFile(getResourcePath() + "grasslandsHex.png")		||
			!texturePointer[woodlandsHex].loadFromFile(getResourcePath() + "woodlandsHex.png")			||
			!texturePointer[deepSeaHex].loadFromFile(getResourcePath() + "deepSeaHex.png")				||
			!texturePointer[randomCityTexture].loadFromFile(getResourcePath() + "randomCityTexture.png")
			
			)	
		{	
			// sfml already prints a message when a texture fails to load.
		}
	}
	return texturePointer[textureIndex];
}
