#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Sprite.h"
#include "Drawable.h"
#include "Health.h"

class Player : public Drawable
{
public:
	Player();
	void setVertexData();
	void keyCallback(int key, int scancode, int action, int modifiers);
	void draw();
	Health playerHealth;
private:
};

#endif
