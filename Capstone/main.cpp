#include <iostream>
#include <GLFW/glfw3.h>
#include "MyWindow.h"
#include "Player.h"

int main()
{
	Player p;
	MyWindow* instance = MyWindow::Instance();
	instance->addKeyCallbackFunction([&](int a, int b, int c, int d) {p.keyCallback(a, b, c, d); });
	instance->setWindowTitle("Something");
	glfwSetKeyCallback(instance->getWindow(), MyWindow::keyCallback);
	while (!glfwWindowShouldClose(instance->getWindow()))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(instance->getWindow());
	}

	return 0;
}