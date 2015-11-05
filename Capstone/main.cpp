#include <iostream>
#include <GLFW/glfw3.h>
#include "MyWindow.h"


int main()
{
	MyWindow window("");
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.getWindow());
	}

	return 0;
}