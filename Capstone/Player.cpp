#ifndef PLAYER_H
#include "Player.h"
#endif

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Player::Player() :
	body(), lance(), xVel(0), yVel(0)
{
}

void Player::keyCallback(int key, int scancode, int action, int modifiers)
{
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		xVel = 0.3;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		xVel = -0.3;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		xVel = 0;
	}
}

void Player::draw()
{
	playerHealth.draw();
	body.draw();
	lance.draw();
	Drawable::draw();
}

void Player::setCollisionPosition()
{
	if (this->getSize().x >= 0)
	{
		body.setPositions(glm::vec2(this->getPosition().x + 116, this->getPosition().y + 11),
			glm::vec2(this->getPosition().x + 162, this->getPosition().y + 75));

		lance.setPositions(glm::vec2(this->getPosition().x + 160, this->getPosition().y + 31),
			glm::vec2(this->getPosition().x + 285, this->getPosition().y + 55));
	}
	else
	{
		body.setPositions(glm::vec2(this->getPosition().x - 116, this->getPosition().y + 11),
			glm::vec2(this->getPosition().x - 162, this->getPosition().y + 75));

		lance.setPositions(glm::vec2(this->getPosition().x - 160, this->getPosition().y + 31),
			glm::vec2(this->getPosition().x - 285, this->getPosition().y + 55));
	}
}

void Player::setPosition(int x, int y)
{
	Drawable::setPosition(x, y);
	setCollisionPosition();
}

void Player::setPosition(glm::vec2 pos)
{
	Drawable::setPosition(pos);
	setCollisionPosition();
}

void Player::update(float t, float dt)
{
	glm::vec2 pos = this->getPosition();
	pos.x += xVel;
	if (pos.x < 0)
	{
		pos.x -= xVel;
	}
	pos.y += yVel;
	if (pos.y < 0)
	{
		pos.y -= yVel;
	}
	Drawable::setPosition(pos);
	setCollisionPosition();
}

void Player::checkForPlayerCollision(Player& p2)
{
	if (lance.collidesWithBox(&p2.lance))
	{
		std::cout << "colliding" << std::endl;
		Drawable::setPosition(getPosition().x - 14, getPosition().y);
		xVel = -.3;
	}
}