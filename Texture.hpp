#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef TEXTURE_H
#define TEXTURE_H




enum TextureIndex
{
	buttonTexture1,

	totalTextures,
};
extern sf::Texture texturePointer[totalTextures];

extern void initTextures();



#endif /* TEXTURE_H */
