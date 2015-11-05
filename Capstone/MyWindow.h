#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>
#include <map>

struct GLFWwindow {};

class MyWindow
{
public:
	MyWindow(std::string title, int width = 800, int height = 600);
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void setWindowTitle(std::string t);
	int getWindowWidth();
	int getWindowHeight();
	GLFWwindow* getWindow();
	std::string getWindowTitle();
private:
	void initWindow();
	void setSize();
	void initGlew();
	void keyCallback(GLFWwindow * window, int key, int scancode, int action, int modifiers);
	GLFWwindow* window;
	int windowWidth, windowHeight;
	std::string windowTitle;

	// HACK: USING MAP WITH VOID POINTERS
	std::map<std::string, void*> stuff;
};

#endif