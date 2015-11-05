#ifndef PLAYER_H
#define PLAYER_H

#include "GLFW/glfw3.h"
#include "Sprite.h"
class Player
{
public:
	Player();
	void keyCallback(int key, int scancode, int action, int modifiers);
	void draw();
private:
	Sprite playerSprite;
};

#endif
