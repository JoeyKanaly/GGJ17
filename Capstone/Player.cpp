#ifndef PLAYER_H
#include "Player.h"
#endif

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Player::Player()
{
	// HACK: TEMP FUNCTION CALL HERE
	setVertexData();
}

void Player::setVertexData()
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

void Player::keyCallback(int key, int scancode, int action, int modifiers)
{
	if (key == GLFW_KEY_P)
	{
		std::cout << "Player key callback function called" << std::endl;
	}
}

void Player::draw()
{
	playerHealth.draw();
	Drawable::draw();
}
