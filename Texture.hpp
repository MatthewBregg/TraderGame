#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef TEXTURE_H
#define TEXTURE_H


enum TextureIndex
{
	buttonTexture1,
	grassLandsHexTexture,

	totalTextures,
};

extern sf::Texture* getTexture(TextureIndex textureIndex);

#endif /* TEXTURE_H */
