#ifndef DRAWABLE_H
#include "Drawable.h"
#endif

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Drawable::Drawable()
{
	shader = loadShader("./shaders/textureDebug.vert.glsl","./shaders/textureDebug.frag.glsl");
	spr = Sprite("./sprites/debug.png");
}

void Drawable::initBuffers()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec4), &data[0], GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Drawable::getScaledSize()
{
	float scalePercentage = 1.0f;
	int tempWidth = spr.getWidth() , tempHeight = spr.getHeight();
	if (size.x == 0.0f && size.y > 0)// && size.y != tempHeight)
	{
		scalePercentage = size.y / tempHeight;
		size.x = tempWidth * scalePercentage;
	}
	else if (size.y == 0.0f && size.x > 0)// && size.x != tempWidth)
	{
		scalePercentage = size.x / tempWidth;
		size.y = tempHeight * scalePercentage;
	}
	else if (size.x <= 0 && size.y <= 0)
	{
		size.x = tempWidth;
		size.y = tempHeight;
	}
}

void Drawable::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VAO);
	GLuint shaderModelMat = glGetUniformLocation(shader, "model");
	GLuint uboIndex = glGetUniformBlockIndex(shader, "mats");
	glm::mat4 model = glm::mat4();

	model = glm::translate(model, glm::vec3(position, 0.0f));
	getScaledSize();
	model = glm::scale(model, glm::vec3(size, 1.0f));
	glUniformMatrix4fv(shaderModelMat, 1, GL_FALSE, glm::value_ptr(model));
	glUniformBlockBinding(shader, uboIndex, 0);
	glBindTexture(GL_TEXTURE_2D, spr.getTexture());

	glDrawArrays(GL_TRIANGLES, 0, data.size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Drawable::setSpritePath(std::string path, bool shouldLoad)
{
	spr.setPath(path, shouldLoad);
}

void Drawable::loadSprite()
{
	spr.load();
}

void Drawable::setPosition(glm::vec2 pos)
{
	position = pos;
}

void Drawable::setPosition(int x, int y)
{
	position = glm::vec2((float)x, (float)y);
}

const glm::vec2 Drawable::getPosition()
{
	return position;
}

void Drawable::setSize(glm::vec2 s)
{
	size = s;
}

void Drawable::setSize(int width, int height)
{
	size = glm::vec2((float)width, (float)height);
}

glm::vec2 Drawable::getSize()
{
	return glm::vec2((size.x == 0) ? spr.getWidth() : size.x,
		(size.y == 0) ? spr.getHeight() : size.y);
}
