#ifndef BOXCOLLIDER_H
#include "BoxCollider.h"
#endif
#include <iostream>
#include "MyWindow.h"
BoxCollider::BoxCollider() :
	topLeft(0.0f, 0.0f), bottomRight(25.0f, 25.0f)
{
}

glm::vec2* getAxes(BoxCollider* box)
{
	static glm::vec2 axes[4];
	for (int i = 0; i < 4; i++)
	{
		glm::vec2 p1 = box->points[i];
		glm::vec2 p2 = box->points[i + 1 == 4 ? 0 : i + 1];
		glm::vec2 edge = p1 - p2;
		glm::vec2 normal = glm::vec2(-edge.y, edge.x);
		axes[i] = normal;
	}
	return axes;
}

Projection BoxCollider::project(glm::vec2 axis)
{
	double min = glm::dot(axis, this->points[0]);
	double max = min;
	for (int i = 1; i < 4; i++)
	{
		double p = glm::dot(axis, this->points[i]);
		if (p < min)
		{
			min = p;
		}
		else if (p > max)
		{
			max = p;
		}
	}
	Projection proj = Projection(min, max);
	return proj;
}

bool BoxCollider::collidesWithBoxSAT(BoxCollider * box)
{
	glm::vec2* axes1 = getAxes(this);
	glm::vec2* axes2 = getAxes(box);

	for (int i = 0; i < 4; i++)
	{
		glm::vec2 axis = axes1[i];
		Projection p1 = this->project(axis);
		Projection p2 = box->project(axis);
		if (!p1.overlap(p2))
		{
			return false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		glm::vec2 axis = axes2[i];
		Projection p1 = this->project(axis);
		Projection p2 = box->project(axis);
		if (!p1.overlap(p2))
		{
			return false;
		}
	}
	return true;
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
	this->setPoints();
}

void BoxCollider::setPoints()
{
	glm::vec2 currentPosition = this->getPosition();
	glm::vec2 currentSize = this->getSize();
	points[0] = glm::vec2(topLeft);
	points[1] = glm::vec2(bottomRight.x, topLeft.y);
	points[2] = glm::vec2(bottomRight);
	points[3] = glm::vec2(topLeft.x, bottomRight.y);
}

glm::vec2 BoxCollider::rotate_point(glm::vec2 position, glm::vec2 origin, float angle)
{
	angle = glm::radians(angle);
	return glm::vec2(cos(angle) * (position.x - origin.x) - sin(angle) * (position.y - origin.y) + origin.x,
		sin(angle) * (position.x - origin.x) + cos(angle) * (position.y - origin.y) + origin.y);
}

void BoxCollider::rotate(float rotationAngle, glm::vec2 origin)
{
	
	//std::cout << "Before: " << points[1].x << ", " << points[1].y;
	for (int i = 0; i < 4; i++)
	{
		points[i] = rotate_point(points[i], origin, rotationAngle);

	}
 	//std::cout << " After: "<< points[1].x << ", " << points[1].y << std::endl;
	

	this->rotationAngle = rotationAngle;
	auto bccx = this->getPosition().x + (this->getSize ().x / 2.0f);
	auto bccy = this->getPosition().y + (this->getSize().y / 2.0f);
	origin = glm::vec2(origin.x - bccx, origin.y - bccy);
	this->origin = origin;
}
