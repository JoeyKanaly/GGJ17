#define GLEW_STATIC
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "MyWindow.h"
#include "Background.h"
#include "Player.h"
#include "Tools.h"
#include "SoundManager.h"
#include "BoxCollider.h"

SoundManager soundManager;

void keyHandler(int key, int scancode, int action, int modifiers);
void mouse(GLFWwindow* window, int button, int action, int mods);
void initPlayers(Player* p1, Player* p2, MyWindow* window);

int main()
{
	double t = 0.0;
	double dt = 1 / 60.0;

	MyWindow* window = MyWindow::Instance();
	window->setWindowSize(1366, 768);
	window->setWindowTitle("High-Speed Jousting Fights");

	soundManager.addSound("backgroundMusic", "./sounds/background.mp3", soundType::BACKGROUND);
	soundManager.addSound("randomEffect", "./sounds/effect.wav", soundType::SOUNDEFFECT);
	
	Background back("./sprites/backgrounds/back_cave.png");
	back.setSize(window->getWindowWidth(), window->getWindowHeight());

	Player p1, p2;
	initPlayers(&p1, &p2, window);

	window->addKeyCallbackFunction([&](int a, int b, int c, int d) {
		p1.keyCallback(a, b, c, d); 
		p2.keyCallback(a, b, c, d);
		keyHandler(a, b, c, d); 
	});
	double currentTime = glfwGetTime();
	double newTime, frameTime;

	//soundManager.playSound("backgroundMusic");

	glfwSetMouseButtonCallback(window->getWindow(), mouse);

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		glfwPollEvents();
		
		newTime = glfwGetTime();
		frameTime = newTime - currentTime;
		currentTime = newTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		back.draw();
		p1.draw();
		p2.draw();
		//printf("(%f, %f) (%f, %f)\n",p2.body.topLeft.x, p2.body.topLeft.y, p2.body.bottomRight.x, p2.body.bottomRight.y);
		while (frameTime > 0.0)
		{
			float deltaTime = std::min(frameTime, dt);
			p1.update(t, deltaTime);
			frameTime -= deltaTime;
			t += deltaTime;
		}
		soundManager.update();
		p1.checkForPlayerCollision(p2);
		glfwSwapBuffers(window->getWindow());
	}

	return 0;
}

void keyHandler(int key, int scancode, int action, int modifiers)
{
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		soundManager.playSound("randomEffect");
	}
	if (key == GLFW_KEY_LEFT_BRACKET)
	{
		soundManager.reduceVolume(soundType::BACKGROUND);
	}
}

// TODO: Move this to MyWindow to have sperate mousecallback functions
void mouse(GLFWwindow* window, int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
	{
		printf("(%f, %f)\n", x, y);
	}
}

void initPlayers(Player* p1, Player* p2, MyWindow* window)
{
	p1->setSpritePath("./sprites/red2x.png");
	p2->setSpritePath("./sprites/purple2x.png");
	p1->setPosition(0, window->getWindowHeight() - p1->getSize().y);
	p2->setSize(-1, 0);
	p2->setPosition(window->getWindowWidth() - p2->getSize().x, window->getWindowHeight() - 88);
	p2->playerHealth.healthYOffset = window->getWindowWidth() - (32 * 3);
}