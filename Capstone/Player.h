#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Sprite.h"
#include "Drawable.h"
#include "Health.h"
#include "BoxCollider.h"

enum Buttons
{
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_DOWN,
	numButtons
};

class Player : public Drawable
{
public:
	Player();
	void keyCallback(int key, int scancode, int action, int modifiers);
	void draw();
	void setPosition(int x, int y);
	void setPosition(glm::vec2 pos);
	Health playerHealth;
	BoxCollider body, lance;
	void update(float t, float dt);
	void checkForPlayerCollision(Player& p2);
	void setButton(Buttons b, int key);
private:
	void setCollisionPosition();
	float xVelocity, yVelocity;
	float xAcceleration, yAcceleration;
	int leftKey, rightKey, upKey, downKey;
	void doPhysics(glm::vec2& pos, float dt);
};

#endif
