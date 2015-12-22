#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <glm\glm.hpp>
#include "Drawable.h"

struct Projection
{
	Projection(float mi, float ma)
	{
		min = mi;
		max = ma;
	}
	bool overlap(Projection p)
	{
		bool isSpearated = p.max < min || max < p.min;
		return !isSpearated;
	}
	float min;
	float max;
};

class BoxCollider : public Drawable
{
public:
	BoxCollider();
	bool collidesWithBoxSAT(BoxCollider* box);
	Projection project(glm::vec2 axis);
	bool collidesWithBox(BoxCollider* box);
	void setPositions(glm::vec2 tL, glm::vec2 bR);
	void setPoints();
	void rotate(float rotationAngle, glm::vec2 origin);
	glm::vec2 rotate_point(glm::vec2 position, glm::vec2 origin, float angle);
	glm::vec2 topLeft, bottomRight;
	glm::vec2 points[4];
	
};

#endif