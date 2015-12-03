#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"
#include "Tools.h"

class Drawable
{
public:
	Drawable();
	void draw();
	void setSpritePath(std::string path, bool shouldLoad = true);
	void loadSprite();
	void setPosition(glm::vec2 pos);
	void setPosition(int x, int y);
	const glm::vec2 getPosition();
	void setSize(glm::vec2 s);
	void setSize(int width, int height);
	glm::vec2 getSize();
protected:
	std::vector<glm::vec4> data;
	void initBuffers();
private:
	void getScaledSize();
	void setVertexData();
	GLuint VBO, VAO;
	GLuint shader;
	Sprite spr;
	glm::vec2 position;
	glm::vec2 size;
};

#endif