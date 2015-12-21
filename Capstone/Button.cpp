#include "Button.h"

Button::Button()
{
}

void Button::setButtonFunction(std::function<void()> bF)
{
	buttonFunction = bF;
}

bool Button::collidesWithMouse(glm::vec2 mousePosition)
{
	auto buttonRightSide = this->getPosition().x + this->getSize().x;
	auto buttonLeftSide = this->getPosition().x;
	auto buttonTopSide = this->getPosition().y;
	auto buttonBottomSide = this->getPosition().y + this->getSize().y;
	if (mousePosition.x < buttonRightSide && mousePosition.x > buttonLeftSide &&
		mousePosition.y > buttonTopSide && mousePosition.y < buttonBottomSide)
	{
		return true;
	}
	return false;
}

bool Button::collidesWithMouse(double x, double y)
{
	return this->collidesWithMouse(glm::vec2(x, y));
}