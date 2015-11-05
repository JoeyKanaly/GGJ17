#ifndef SPRITE_H
#include "Sprite.h"
#endif

#define GLEW_STATIC
#include <GL/glew.h>

Sprite::Sprite() :
	spritePath(""), imageWidth(0), imageHeight(0)
{

}

void Sprite::setPath(std::string p)
{
	spritePath = p;
}

void Sprite::load()
{
	image = SOIL_load_image(spritePath.c_str(), &imageWidth, &imageHeight, nullptr, SOIL_LOAD_RGBA);
}

GLuint Sprite::getTexture()
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
