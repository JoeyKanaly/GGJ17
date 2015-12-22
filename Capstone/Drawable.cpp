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
	rotationAngle = 0.0f;
	setVertexData();
	center = glm::vec2();
}

void Drawable::setVertexData()
{
	glm::vec4 v(0.0f, 1.0f, 0.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
	data.push_back(v);

	v = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	data.push_back(v);

	v = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
	data.push_back(v);
	initBuffers();
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
	int tempWidth = spr.getWidth(), tempHeight = spr.getHeight();
	if (size.x == 0.0f && size.y > 0)// && size.y != tempHeight)
	{
		scalePercentage = size.y / tempHeight;
		size.x = tempWidth * scalePercentage;
	}
	else if (size.y == 0.0f && size.x > 0.0f)// && size.x != tempWidth)
	{
		scalePercentage = size.x / tempWidth;
		size.y = tempHeight * scalePercentage;
	}
	else if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = tempWidth;
		size.y = tempHeight;
	}
	if (size.x == -1.0f)
	{
		size.x = -tempWidth;
	}
	if (size.y == -1.0f)
	{
		size.y = -tempHeight;
	}
	else if(size.y == 0)
	{
		size.y = tempHeight;
	}
}

void Drawable::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VAO);
	GLuint shaderModelMat = glGetUniformLocation(shader, "model");
	GLuint uboIndex = glGetUniformBlockIndex(shader, "mats");
	model = glm::mat4();
	getScaledSize();

	if (center.x == 0 && center.y == 0)
	{
		center = glm::vec2(size.x / 2.0f, size.y / 2.0f);
	}

	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(center, 0.0f));
	model = glm::translate(model, glm::vec3(origin, 0.0f));
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-origin, 0.0f));
	model = glm::translate(model, glm::vec3(-center, 0.0f));
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
