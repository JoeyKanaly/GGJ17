#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Sprite.h"
#include "Drawable.h"
#include "BoxCollider.h"
#include "SoundManager.h"
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
	void update();
	void setButton(Buttons b, int key);
	SoundManager* sm;
private:
	float acceleration, rotationAcceleration;
	int leftKey, rightKey, upKey, downKey;
	void doPhysics(glm::vec2& pos, float dt);
	float lastHit;
	float speed, rotationSpeed;
	bool pressed[numButtons];
};

#endif
