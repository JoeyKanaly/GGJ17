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
#include "Menu.h"

enum gameState
{
	MAINMENU,
	PLAY,
	GAMEOVER,
	GAMESTATECOUNT
};

SoundManager soundManager;

int main();

void keyHandler(int key, int scancode, int action, int modifiers);

int main()
{
	MyWindow* window = MyWindow::Instance();

	window->setWindowSize(1366, 768);
	window->setWindowTitle("High-Speed Jousting Fights");

	/*soundManager.addSound("backgroundMusic", "./sounds/background.mp3", soundType::BACKGROUND);
	soundManager.addSound("randomEffect", "./sounds/effect.wav", soundType::SOUNDEFFECT);*/
	
	Background back("./sprites/backgrounds/back.png");
	back.setSize(window->getWindowWidth(), window->getWindowHeight());

	Player player;
	player.setSpritePath("./sprites/FOO.png");
	
	window->addKeyCallbackFunction([&](int a, int b, int c, int d) {
		keyHandler(a, b, c, d);
		player.keyCallback(a, b, c, d);
	});
	window->addMouseButtonCallbackFunction([&](int a, int b, int c, glm::vec2 d) {

	});
	
	/*soundManager.setVolume(soundType::BACKGROUND, .25);
	soundManager.setVolume(soundType::SOUNDEFFECT, .25);
	player.sm = &soundManager;*/

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		back.draw();
		player.draw();

		player.update();

		soundManager.update();
		glfwSwapBuffers(window->getWindow());
	}

	return 0;
}



void keyHandler(int key, int scancode, int action, int modifiers)
{
	if (key == GLFW_KEY_Y && action == GLFW_RELEASE)
	{
		soundManager.playSound("randomEffect");
	}
	if (key == GLFW_KEY_LEFT_BRACKET)
	{
		soundManager.reduceVolume(soundType::BACKGROUND);
	}
	if (key == GLFW_KEY_RIGHT_BRACKET)
	{
		soundManager.increaseVolume(soundType::BACKGROUND);
	}
}