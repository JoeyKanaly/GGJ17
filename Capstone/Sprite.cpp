#ifndef SPRITE_H
#include "Sprite.h"
#endif

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

std::vector<Texture> Sprite::loadedTextures;

Sprite::Sprite() :
	spritePath(""), imageWidth(0), imageHeight(0)
{

}

Sprite::Sprite(std::string path) :
	spritePath(path), imageWidth(0), imageHeight(0)
{
	load();
}

void Sprite::setPath(std::string p, bool shouldLoad)
{
	spritePath = p;
	if(shouldLoad)
		load();
}

void Sprite::load()
{
	bool shouldSkip = false;

	for (int i = 0; i < loadedTextures.size(); i++)
	{
		if (loadedTextures[i].path == spritePath)
		{
			shouldSkip = true;
			texture = loadedTextures[i].textureID;
		}
	}
	if (!shouldSkip)
	{
		image = SOIL_load_image(spritePath.c_str(), &imageWidth, &imageHeight, nullptr, SOIL_LOAD_RGBA);
		if (image == 0)
		{
			Log::instance()->writeToLog("Unable to load image at: \"" + spritePath + "\"");
			Texture t;
			t.path = spritePath;
			t.textureID = NULL;
			loadedTextures.push_back(t);
		}
		else
		{
			generateTexture();
		}
		SOIL_free_image_data(image);
	}
}

void Sprite::generateTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	Texture t;
	t.path = spritePath;
	t.textureID = texture;
	loadedTextures.push_back(t);
}

int Sprite::getWidth()
{
	return imageWidth;
}

int Sprite::getHeight()
{
	return imageHeight;
}

GLuint Sprite::getTexture()
{
	return texture;
}
