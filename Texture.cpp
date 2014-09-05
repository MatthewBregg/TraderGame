#include <iostream>
#include "GlobalValues.h"


#include "Texture.h"


const sf::Texture& getTexture(TextureIndex textureIndex)
{
	static sf::Texture texturePointer[totalTextures];	

	if (texturePointer[textureIndex].getSize().x == 0 && texturePointer[textureIndex].getSize().y == 0)
	{
		texturePointer[randomBg].loadFromFile(getResourcePath() + "randomBg.png");
		texturePointer[button1].loadFromFile(getResourcePath() + "button1.png");
		texturePointer[grassLandsHex].loadFromFile(getResourcePath() + "grasslandsHex.png");
		texturePointer[woodlandsHex].loadFromFile(getResourcePath() + "woodlandsHex.png");
		texturePointer[hillHex].loadFromFile(getResourcePath() + "hillHex.png");
		texturePointer[deepSeaHex].loadFromFile(getResourcePath() + "deepSeaHex.png");

		texturePointer[randomCityTexture].loadFromFile(getResourcePath() + "randomCityTexture.png");
		texturePointer[tradeCentreTexture].loadFromFile(getResourcePath() + "tradeCentreTexture.png");
			
		// sfml already prints a message when a texture fails to load, so no need to check 
		// if the texture is fine.

	for (int i = 0; i < textureIndex; ++i)
	    {
		texturePointer[i].setSmooth(true);
	    }
	}
	return texturePointer[textureIndex];
}
