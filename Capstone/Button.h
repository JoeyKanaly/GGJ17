#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "Drawable.h"

class Button : public Drawable
{
public:
	Button();
	void setButtonFunction(std::function<void()> bF);
	bool collidesWithMouse(glm::vec2 mousePosition);
	bool collidesWithMouse(double x, double y);
	std::function<void()> buttonFunction;
};

#endif // !BUTTON_H
