#define GLEW_STATIC
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "MyWindow.h"
#include "Player.h"

void generateUBO(glm::mat4& projection)
{
	GLuint UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), glm::value_ptr(projection), GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

int main()
{
	MyWindow* window = MyWindow::Instance();
	Log::instance();
	window->setWindowTitle("High-Speed Jousting Fights");
	glfwSetKeyCallback(window->getWindow(), MyWindow::keyCallback);

	glm::mat4 projection = glm::ortho(0.0f, (float)window->getWindowWidth(), (float)window->getWindowHeight(), 0.0f);
	generateUBO(projection);
	
	Player p1, p2;
	p1.setSpritePath("./sprites/red2x.png");
	p1.setPosition(0, window->getWindowHeight() - 88);

	p2.setSpritePath("./sprites/purple2x.png");
	p2.setPosition(window->getWindowWidth() -284, window->getWindowHeight() - 88);
	p2.playerHealth.healthYOffset = window->getWindowWidth() - (32 * 3);

	window->addKeyCallbackFunction([&](int a, int b, int c, int d) {p1.keyCallback(a, b, c, d); p2.keyCallback(a, b, c, d); });
	double lastTime, currentTime = 0, deltaTime;
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		glfwPollEvents();
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		p1.draw();
		p2.draw();
		glfwSwapBuffers(window->getWindow());
	}

	return 0;
}