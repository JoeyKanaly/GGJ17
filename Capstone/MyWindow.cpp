#define GLEW_STATIC
#ifndef MYWINDOW_H
#include "MyWindow.h"
#endif

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

MyWindow* MyWindow::m_pInstance = NULL;

MyWindow::MyWindow() :
	windowTitle(""), windowWidth(800), windowHeight(600), resized(false)
{
	// TODO: ERROR HANDLING
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

void MyWindow::setWindowSize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	setSize();
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
	projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f);

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
	
	if (window == nullptr)
	{
		Log::instance()->writeToLog("Window was unable to initialize.");
		// HACK: EXIT USED
		exit(0);
	}
	glViewport(0, 0, windowWidth, windowHeight);
	glfwMakeContextCurrent(window);
	initGlew();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetKeyCallback(window, MyWindow::keyCallback);
	glfwSetWindowSizeCallback(window, MyWindow::resizeCallback);
	generateUBO();
}

void MyWindow::setSize()
{
	projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f);
	updateUBO();
	glfwSetWindowSize(window, windowWidth, windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
}

void MyWindow::initGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::instance()->writeToLog("GLEW was unable to initialize.");
		// HACK: EXIT USED
		exit(0);
	}
}

void MyWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	Instance()->keyCallbackImpl(key, scancode, action, modifiers);
}

void MyWindow::resizeCallback(GLFWwindow* window, int width, int height)
{
	Instance()->resizeCallbackImpl(width, height);
}

void MyWindow::keyCallbackImpl(int key, int scanCode, int action, int modifiers)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, 1);
	}
	for (int i = 0; i < keyCalls.size(); i++)
	{
		keyCalls[i](key, scanCode, action, modifiers);
	}
}

void MyWindow::resizeCallbackImpl(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	setSize();
	resized = true;
}

void MyWindow::generateUBO()
{
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), glm::value_ptr(projection), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void MyWindow::updateUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}