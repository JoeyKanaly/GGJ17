#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>



class MyWindow
{
public:
	MyWindow(std::string title, int width = 800, int height = 600);
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void setWindowTitle(std::string t);
	int getWindowWidth();
	int getWindowHeight();
	std::string getWindowTitle();
private:
	void initWindow();
	void setSize();
	GLFWwindow* window;
	int windowWidth, windowHeight;
	std::string windowTitle;
};

#endif