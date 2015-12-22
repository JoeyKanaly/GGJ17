#ifndef HEALTH_H
#define HEALTH_H
#include "Drawable.h"

#include <algorithm>

class Health : public Drawable
{
public:
	Health();
	void reduceHealth(int reduceAmount);
	void reset();
	int getCurrentHealth();
	void setMaxHealth(int max);
	int getMaxHealth();
	void draw();
	// HACK: THIS SHOULDN'T BE PUBLIC
	int healthYOffset;
protected:
private:
	int maxHealth, currentHealth;
};
#endif