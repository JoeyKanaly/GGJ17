#ifndef MENU_H
#include "Menu.h"
#endif // !MENU_H

#include "MyWindow.h"

Menu::Menu()
{
	back = Background();
	back.setSize(MyWindow::Instance()->getWindowWidth(), MyWindow::Instance()->getWindowHeight());
}

void Menu::addButton(std::string name, glm::vec2 position, glm::vec2 size)
{
	Button tempButton;
	tempButton.setPosition(position);
	tempButton.setSize(size);
	buttons.insert(std::make_pair(name, tempButton));
}

void Menu::addButton(std::string name, float x, float y, float w, float h)
{
	this->addButton(name, glm::vec2(x, y), glm::vec2(w, h));
}

void Menu::setButtonSprite(std::string buttonName, std::string path)
{
	buttons[buttonName].setSpritePath(path);
}

void Menu::setButtonSize(std::string buttonName, glm::vec2 size)
{
	buttons[buttonName].setSize(size);
}

void Menu::setButtonSize(std::string buttonName, float w, float h)
{
	this->setButtonSize(buttonName, glm::vec2(w, h));
}

void Menu::setButtonPosition(std::string buttonName, glm::vec2 position)
{
	buttons[buttonName].setPosition(position);
}

void Menu::setButtonPosition(std::string buttonName, float x, float y)
{
	this->setButtonPosition(buttonName, glm::vec2(x, y));
}

void Menu::draw()
{
	back.draw();
	for (auto &ent1 : buttons)
	{
		ent1.second.draw();
	}
}

void Menu::mouseButton(int button, int action, int mods, glm::vec2 mousePosition)
{
	for (auto &ent1 : buttons)
	{
		if (ent1.second.collidesWithMouse(mousePosition))
		{
			ent1.second.buttonFunction();
		}
	}
}

void Menu::setButtonClickFunction(std::string buttonName, std::function<void()> func)
{
	buttons[buttonName].buttonFunction = func;
}
