#define GLEW_STATIC
#ifndef MYWINDOW_H
#include "MyWindow.h"
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MyWindow* MyWindow::m_pInstance = NULL;

MyWindow::MyWindow() :
	windowTitle(""), windowWidth(800), windowHeight(600)
{
	glfwInit();
	initWindow();
}

MyWindow * MyWindow::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyWindow();
	}

	return m_pInstance;
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
	glfwSetWindowTitle(window, windowTitle.c_str());
}

int MyWindow::getWindowWidth()
{
	return windowWidth;
}

int MyWindow::getWindowHeight()
{
	return windowHeight;
}

GLFWwindow * MyWindow::getWindow()
{
	return window;
}

std::string MyWindow::getWindowTitle()
{
	return windowTitle;
}

void MyWindow::addKeyCallbackFunction(std::function<void(int, int, int, int)> func)
{
	keyCalls.push_back(func);
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
		exit(0);
	}
	glfwMakeContextCurrent(window);
	initGlew();
	glViewport(0, 0, windowWidth, windowHeight);
}

void MyWindow::setSize()
{
	glfwSetWindowSize(window, windowWidth, windowHeight);
}

void MyWindow::initGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// TODO: Add logging
		// HACK: EXIT USED
		exit(0);
	}
}

void MyWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	Instance()->keyCallbackImpl(key, scancode, action, modifiers);
}

void MyWindow::keyCallbackImpl(int key, int scanCode, int action, int modifiers)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, 1);
	}
	for (int i = 0; i < keyCalls.size(); i++)
	{

		keyCalls.at(i)(key, scanCode, action, modifiers);
	}
}
