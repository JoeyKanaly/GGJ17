#ifndef PLAYER_H
#include "Player.h"
#endif

#include <iostream>

Player::Player() :
	playerSprite()
{

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
}
