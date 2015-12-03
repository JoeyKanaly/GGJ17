#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Sprite.h"
#include "Drawable.h"
#include "Health.h"
#include "BoxCollider.h"

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
private:
	void setCollisionPosition();
	float xVel, yVel;

};

#endif
