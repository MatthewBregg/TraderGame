#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef TEXTURE_H
#define TEXTURE_H

// All TextureIndex names should match the name of the texture itself.  

enum TextureIndex
{
	genericBg,
	button1,
	grassLandsHex,
	woodlandsHex,
	hillHex,
	deepSeaHex,

	randomCityTexture,
	tradeCentreTexture,

	totalTextures,
};

// Loads textures on demand.
extern const sf::Texture& getTexture(TextureIndex textureIndex);

#endif /* TEXTURE_H */
