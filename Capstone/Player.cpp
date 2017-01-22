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
	leftKey(GLFW_KEY_A), rightKey(GLFW_KEY_D),
	upKey(GLFW_KEY_W), downKey(GLFW_KEY_S),
	speed(0), lastHit(0)
{
}

void Player::keyCallback(int key, int scancode, int action, int modifiers)
{
	if (key == leftKey && action == GLFW_PRESS)
	{
		pressed[BUTTON_LEFT] = true;
	}
	if (key == rightKey && action == GLFW_PRESS)
	{
		pressed[BUTTON_RIGHT] = true;
	}
	if (key == upKey && action == GLFW_PRESS)
	{
		pressed[BUTTON_UP] = true;
	}
	if (key == downKey && action == GLFW_PRESS)
	{
		pressed[BUTTON_DOWN] = true;
	}

	if (key == leftKey && action == GLFW_RELEASE)
	{
		pressed[BUTTON_LEFT] = false;
	}
	if (key == rightKey && action == GLFW_RELEASE)
	{
		pressed[BUTTON_RIGHT] = false;
	}
	if (key == upKey && action == GLFW_RELEASE)
	{
		pressed[BUTTON_UP] = false;
	}
	if (key == downKey && action == GLFW_RELEASE)
	{
		pressed[BUTTON_DOWN] = false;
	}
}

void Player::draw()
{
	Drawable::draw();
}

void Player::setPosition(int x, int y)
{
	Drawable::setPosition(x, y);
	//setCollisionPosition();
}

void Player::setPosition(glm::vec2 pos)
{
	Drawable::setPosition(pos);
	//setCollisionPosition();
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

void Player::update()
{
	float speed = 5.0f;
	glm::vec2 pos = getPosition();
	if (pressed[BUTTON_LEFT])
		pos.x -= speed;
	if (pressed[BUTTON_RIGHT])
		pos.x += speed;
	if (pressed[BUTTON_UP])
		pos.y -= speed;
	if (pressed[BUTTON_DOWN])
		pos.y += speed;

	MyWindow* window = MyWindow::Instance();
	glm::vec2 size = getSize();
	pos.x = (pos.x > 0) ? ((pos.x + size.x < window->getWindowWidth()) ? pos.x : window->getWindowWidth()- size.x-1) : 0+1;
	pos.y = (pos.y > 0) ? ((pos.y + size.y < window->getWindowHeight()) ? pos.y : window->getWindowHeight()-size.y-1) : 0+1;

	Drawable::setPosition(pos);
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
