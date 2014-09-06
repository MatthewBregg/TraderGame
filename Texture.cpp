#include <iostream>
#include "GlobalValues.h"


#include "Texture.h"

// Loads textures on demand.
const sf::Texture& getTexture(TextureIndex textureIndex)
{
	static sf::Texture texturePointer[totalTextures];	

	// Texture haven't been loaded properly. 
	if (texturePointer[textureIndex].getSize().x == 0 && texturePointer[textureIndex].getSize().y == 0)
	{
		texturePointer[genericBg].loadFromFile(getResourcePath() + "genericBg.png");
		texturePointer[button1].loadFromFile(getResourcePath() + "button1.png");
		texturePointer[grassLandsHex].loadFromFile(getResourcePath() + "grasslandsHex.png");
		texturePointer[woodlandsHex].loadFromFile(getResourcePath() + "woodlandsHex.png");
		texturePointer[hillHex].loadFromFile(getResourcePath() + "hillHex.png");
		texturePointer[deepSeaHex].loadFromFile(getResourcePath() + "deepSeaHex.png");

		texturePointer[randomCityTexture].loadFromFile(getResourcePath() + "randomCityTexture.png");
		texturePointer[tradeCentreTexture].loadFromFile(getResourcePath() + "tradeCentreTexture.png");
			
		texturePointer[goldIcon].loadFromFile(getResourcePath() + "goldIcon.png");
		texturePointer[foodIcon].loadFromFile(getResourcePath() + "foodIcon.png");
		texturePointer[woodIcon].loadFromFile(getResourcePath() + "woodIcon.png");
		texturePointer[steelIcon].loadFromFile(getResourcePath() + "steelIcon.png");

		// sfml already prints a message when a texture fails to load, so no need to check 
		// if the texture is fine.

		for (int i = 0; i < textureIndex; ++i)
	    {
			texturePointer[i].setSmooth(true);
	    }
	}
	return texturePointer[textureIndex];
}
