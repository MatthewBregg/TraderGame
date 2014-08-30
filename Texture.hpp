#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef TEXTURE_H
#define TEXTURE_H

// All TextureIndex names should match the name of the texture itself.  

enum TextureIndex
{
	buttonTexture1,
	grassLandsHex,
	woodlandsHex,
	hillHex,
	deepSeaHex,

	randomCityTexture,

	totalTextures,
};

extern const sf::Texture& getTexture(TextureIndex textureIndex);

#endif /* TEXTURE_H */
