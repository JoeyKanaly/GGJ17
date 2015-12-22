#ifndef PLAYER_H
#include "Player.h"
#endif

#include "MyWindow.h"
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <cmath>
#include <math.h>

Player::Player() :
	body(), lance(),
	leftKey(GLFW_KEY_A), rightKey(GLFW_KEY_D),
	upKey(GLFW_KEY_W), downKey(GLFW_KEY_S),
	speed(0), lastHit(0)
{
}

void Player::keyCallback(int key, int scancode, int action, int modifiers)
{
	float acc = 500.0f;
	float rotAcc = 150.0f;
	if (key == rightKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//yAcceleration = 100;
		/*this->rotationAngle += 10.0f;
		if (rotationAngle > 360)
		{
			this->rotationAngle -= 360.0f;
		}*/
		rotationAcceleration = rotAcc;
	}
	if (key == leftKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//yAcceleration = -100;
		/*this->rotationAngle -= 10.0f;

		if (rotationAngle < -360)
		{
			this->rotationAngle += 360.0f;
		}*/
		rotationAcceleration = -rotAcc;
	}
	if (key == upKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//xAcceleration = 100;
		acceleration = acc;
	}
	if (key == downKey && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//xAcceleration = -100;
		acceleration = -acc;
	}
	if ((key == upKey || key == downKey) && action == GLFW_RELEASE)
	{
		//xAcceleration = 0;
		acceleration = 0;
	}
	if ((key == leftKey || key == rightKey) && action == GLFW_RELEASE)
	{
		//yAcceleration = 0;
		rotationAcceleration = 0;
	}
}

void Player::draw()
{
	//body.draw();
	//lance.draw();
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

	glm::vec2 origin = glm::vec2((this->getPosition().x + (this->getSize().x / 2.0f)), (this->getPosition().y + (this->getSize().y / 2.0f)));
	body.rotate(this->rotationAngle, origin);
	lance.rotate(this->rotationAngle, origin);
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
	/*pos.x += ((xVelocity * cos(glm::radians(rotationAngle))) * dt);
	pos.y += ((yVelocity * sin(glm::radians(rotationAngle))) * dt);
	xVelocity += (xAcceleration * dt);
	yVelocity += (yAcceleration * dt);*/
	pos.x += cos(2 * 3.14 * (rotationAngle / 360)) * speed * dt;
	pos.y += sin(2 * 3.14 * (rotationAngle / 360)) * speed * dt;
	speed += acceleration * dt;
	rotationAngle += rotationAcceleration * dt;
	
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
			speed = 0;
			//xVelocity = 0;
		}
		else
		{
			pos.x = MyWindow::Instance()->getWindowWidth() - this->getSize().x;
			speed = 0;
			//xVelocity = 0;
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
			speed = 0;
			//xVelocity = 0;
		}
		else
		{
			pos.x = MyWindow::Instance()->getWindowWidth();
			speed = 0;
			//xVelocity = 0;
		}
	}
	if (pos.y < 0)
	{
		pos.y = 0;
		//yVelocity = 0;
	}
	else if (pos.y > MyWindow::Instance()->getWindowHeight() - this->getSize().y)
	{
		pos.y = MyWindow::Instance()->getWindowHeight() - this->getSize().y;
		//yVelocity = 0;
	}
	Drawable::setPosition(pos);
	setCollisionPosition();
}

void Player::checkForPlayerCollision(Player& p2)
{
	if (lance.collidesWithBoxSAT(&p2.lance))
	{
		//Drawable::setPosition(getPosition().x - 14, getPosition().y);
		if (this->getSize().x < 0)
			speed = 1200;
		else
			speed = -1200;
	}
	else if (lance.collidesWithBoxSAT(&p2.body))
	{
		if (glfwGetTime() - lastHit > 1 || lastHit == 0)
		{
			p2.playerHealth.reduceHealth(1);
			lastHit = glfwGetTime();
		}
		if (this->getSize().x < 0)
			speed = 1200;
		else
			speed = -1200;
	}
	if (lance.collidesWithBoxSAT(&p2.lance) && !lance.collidesWithBoxSAT(&p2.body))
	{
		sm->playSound("randomEffect");
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
