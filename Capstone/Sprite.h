#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <SOIL2/SOIL2.h>

class Sprite
{
public:
	Sprite();
	void setPath(std::string p);
	void load();
	GLuint getTexture();
private:
	std::string spritePath;
	int imageWidth, imageHeight;
	unsigned char* image;
};

#endif
