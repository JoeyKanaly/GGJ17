#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>
#include <vector>
#include <functional>
#include <glm\gtc\matrix_transform.hpp>
#include "Log.h"

struct GLFWwindow {};

class MyWindow
{
public:
	static MyWindow* Instance();
	void setWindowSize(int w, int h);
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void setWindowTitle(std::string t);
	int getWindowWidth();
	int getWindowHeight();
	GLFWwindow* getWindow();
	std::string getWindowTitle();
	void addKeyCallbackFunction(std::function<void(int, int, int, int)> func);
	void addMouseButtonCallbackFunction(std::function<void(int, int, int, glm::vec2)> func);
	static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int modifiers);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	bool resized;
private:
	MyWindow();
	MyWindow(MyWindow const&) {};
	MyWindow operator=(const MyWindow& a) {};
	static MyWindow* m_pInstance;
	void initWindow();
	void setSize();
	void initGlew();
	void keyCallbackImpl(int key, int scanCode, int action, int modifiers);
	void resizeCallbackImpl(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);
	void mouseButtonCallbackImpl(int button, int action, int mods, glm::vec2 mousePosition);
	GLFWwindow* window;
	int windowWidth, windowHeight;
	std::string windowTitle;
	std::vector<std::function<void(int, int, int, int)>> keyCalls;
	std::vector<std::function<void(int, int, int, glm::vec2)>> mouseButtonCalls;
	glm::mat4 projection;
	GLuint UBO;
	void generateUBO();
	void updateUBO();
};

#endif