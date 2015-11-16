#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
typedef unsigned int GLuint;
#include <glm/glm.hpp>
#include <SOIL2/SOIL2.h>
#include "Log.h"

struct Texture
{
	GLuint textureID;
	std::string path;
};

class Sprite
{
public:
	Sprite();
	Sprite(std::string path);
	void setPath(std::string p, bool shouldLoad = true);
	void load();
	void generateTexture();
	int getWidth();
	int getHeight();
	GLuint getTexture();
	static std::vector<Texture> loadedTextures;
private:
	GLuint texture;
	std::string spritePath;
	int imageWidth, imageHeight;
	unsigned char* image;
};

#endif
