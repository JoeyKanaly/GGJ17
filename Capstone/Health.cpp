#ifndef HEALTH_H
#include "Health.h"
#endif

Health::Health() :
	maxHealth(3), currentHealth(3), healthYOffset(0)
{
	glm::vec4 v(0.0f, 1.0f, 0.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
	data.push_back(v);
	v = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	data.push_back(v);

	v = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data.push_back(v);

	v = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
	data.push_back(v);
	initBuffers();
}

void Health::reduceHealth(int reduceAmount)
{
	currentHealth = std::max(currentHealth - reduceAmount, 0);
}

void Health::reset()
{
	currentHealth = maxHealth;
}

int Health::getCurrentHealth()
{
	return currentHealth;
}

void Health::setMaxHealth(int max)
{
	maxHealth = max;
}

int Health::getMaxHealth()
{
	return maxHealth;
}

void Health::draw()
{
	setSize(0,32);
	int tempYOffset = healthYOffset;
	setSpritePath("./sprites/heart-full.png");
	for (int i = 0; i < currentHealth; i++)
	{
		setPosition(tempYOffset, 0);
		Drawable::draw();
		tempYOffset += getSize().x;
	}

	setSpritePath("./sprites/heart-empty.png");
	for (int i = 0; i < maxHealth - currentHealth; i++)
	{
		setPosition(tempYOffset, 0);
		Drawable::draw();
		tempYOffset += getSize().x;
	}
}
