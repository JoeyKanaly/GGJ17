#ifndef MYWINDOW_H
#include "MyWindow.h"
#endif
#include <GLFW/glfw3.h>

MyWindow::MyWindow(std::string title, int width, int height) :
	windowTitle(title), windowWidth(width), windowHeight(height)
{
	glfwInit();
	initWindow();
}

void MyWindow::setWindowWidth(int w)
{
	windowWidth = w;
	setSize();
}

void MyWindow::setWindowHeight(int h)
{
	windowHeight = h;
	setSize();
}

void MyWindow::setWindowTitle(std::string t)
{
	windowTitle = t;
}

int MyWindow::getWindowWidth()
{
	return windowWidth;
}

int MyWindow::getWindowHeight()
{
	return windowHeight;
}

std::string MyWindow::getWindowTitle()
{
	return windowTitle;
}

void MyWindow::initWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// TODO: Handle Resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
	
	if (window == nullptr)
	{
		// TODO: Add logging
		// HACK: EXIT USED
		exit;
	}

	glfwMakeContextCurrent(window);
}

void MyWindow::setSize()
{
	glfwSetWindowSize(window, windowWidth, windowHeight);
}