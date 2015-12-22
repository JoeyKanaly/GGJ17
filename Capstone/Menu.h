#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "Background.h"
#include <map>

class Menu
{
public:
	Menu();
	void addButton(std::string name, glm::vec2 position, glm::vec2 size);
	void addButton(std::string name, float x = 0.0f, float y = 0.0f, float w = 100.0f, float h = 50.0f);
	void setButtonSprite(std::string buttonName, std::string path);
	void setButtonSize(std::string buttonName, glm::vec2 size);
	void setButtonSize(std::string buttonName, float w, float h);
	void setButtonPosition(std::string buttonName, glm::vec2 position);
	void setButtonPosition(std::string buttonName, float x, float y);
	void draw();
	void mouseButton(int button, int action, int mods, glm::vec2 mousePosition);
	void setButtonClickFunction(std::string buttonName, std::function<void()> func);
	Background back;
	bool shouldCheckForMouse;

private:
	std::map<std::string, Button> buttons;
};

#endif // !MENU_H
