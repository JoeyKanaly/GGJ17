#ifndef PLAYER_H
#include "Player.h"
#endif

#include "MyWindow.h"
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

Player::Player() :
	body(), lance(), xVelocity(0), yVelocity(0),
	leftKey(GLFW_KEY_A), rightKey(GLFW_KEY_D),
	upKey(GLFW_KEY_W), downKey(GLFW_KEY_S)
{
}

void Player::keyCallback(int key, int scancode, int action, int modifiers)
{
	if (key == rightKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		xAcceleration = 100;
	}
	if (key == leftKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		xAcceleration = -100;
	}
	if (key == upKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		yAcceleration = -100;
	}
	if (key == downKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		yAcceleration = 100;
	}
	if ((key == upKey || key == downKey) && action == GLFW_RELEASE)
	{
		yAcceleration = 0;
	}
	if ((key == leftKey || key == rightKey) && action == GLFW_RELEASE)
	{
		xAcceleration = 0;
	}
}

void Player::draw()
{
	Drawable::draw();
	playerHealth.draw();
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

void Player::doPhysics(glm::vec2& pos, float dt)
{
	pos.x += (xVelocity * dt);
	pos.y += (yVelocity * dt);
	xVelocity += (xAcceleration * dt);
	yVelocity += (yAcceleration * dt);
}

void Player::update(float t, float dt)
{
	glm::vec2 pos = this->getPosition();
	/*
	 * Acceleration = deltaVelocity/deltaTime
	 * Acceleration * deltaTime = deltaVelocity
	 *
	 */

	/*
	pos.x += xVelocity;
	if (pos.x < 0)
	{
		pos.x -= xVelocity;
	}
	pos.y += yVelocity;
	if (pos.y < 0)
	{
		pos.y -= yVelocity;
	}*/
	if (this->getSize().x > 0)
	{
		if (pos.x >= 0 && pos.x + this->getSize().x <= MyWindow::Instance()->getWindowWidth())
		{
			doPhysics(pos, dt);
		}
		else if(pos.x < 0)
		{
			pos.x = 0;
			xVelocity = 0;
		}
		else
		{
			pos.x = MyWindow::Instance()->getWindowWidth() - this->getSize().x;
			xVelocity = 0;
		}
	}
	else
	{
		if(pos.x >= abs(this->getSize().x) && pos.x <= MyWindow::Instance()->getWindowWidth())
		{
			doPhysics(pos, dt);
		}
		else if(pos.x <= abs(this->getSize().x))
		{
			pos.x = abs(this->getSize().x);
			xVelocity = 0;
		}
		else
		{
			pos.x = MyWindow::Instance()->getWindowWidth();
			xVelocity = 0;
		}
	}
	if (pos.y < 0)
	{
		pos.y = 0;
		yVelocity = 0;
	}
	else if (pos.y > MyWindow::Instance()->getWindowHeight() - this->getSize().y)
	{
		pos.y = MyWindow::Instance()->getWindowHeight() - this->getSize().y;
		yVelocity = 0;
	}
	Drawable::setPosition(pos);
	setCollisionPosition();
}

void Player::checkForPlayerCollision(Player& p2)
{
	if (lance.collidesWithBox(&p2.lance))
	{
		std::cout << "colliding" << std::endl;
		//Drawable::setPosition(getPosition().x - 14, getPosition().y);
		if (this->getSize().x < 0)
			xVelocity = 1200;
		else
			xVelocity = -1200;
		yVelocity = -100;
	}
}

void Player::setButton(Buttons b, int key)
{
	switch (b)
	{
	case BUTTON_LEFT:
		leftKey = key;
		break;
	case BUTTON_RIGHT:
		rightKey = key;
		break;
	case BUTTON_UP:
		upKey = key;
		break;
	case BUTTON_DOWN:
		downKey = key;
		break;
	}
}
