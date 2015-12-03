#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <glm\glm.hpp>
#include "Drawable.h"

class BoxCollider : public Drawable
{
public:
	BoxCollider();
	bool collidesWithBox(BoxCollider* box);
	void setPositions(glm::vec2 tL, glm::vec2 bR);
	glm::vec2 topLeft, bottomRight;
};

#endif