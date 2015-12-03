#ifndef BOXCOLLIDER_H
#include "BoxCollider.h"
#endif

BoxCollider::BoxCollider() :
	topLeft(0.0f, 0.0f), bottomRight(25.0f, 25.0f)
{
}

bool BoxCollider::collidesWithBox(BoxCollider * box)
{
	if (this->topLeft.x <= box->bottomRight.x &&
		this->bottomRight.x >= box->topLeft.x &&
		this->topLeft.y <= box->bottomRight.y &&
		this->bottomRight.y >= box->topLeft.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BoxCollider::setPositions(glm::vec2 tL, glm::vec2 bR)
{
	// TODO: Handle bottomRight being in a lower x/y position
	if (tL.x > bR.x)
	{
		topLeft.x = bR.x;
		bottomRight.x = tL.x;
	}
	else
	{
		topLeft.x = tL.x;
		bottomRight.x = bR.x;
	}
	if (tL.y > bR.y)
	{
		topLeft.y = bR.y;
		bottomRight.y = tL.y;
	}
	else
	{
		topLeft.y = tL.y;
		bottomRight.y = bR.y;
	}
	this->setPosition(tL);
	this->setSize(bR.x - tL.x, bR.y - tL.y);
}