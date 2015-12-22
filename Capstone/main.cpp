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
void initPlayers(Player& p1, Player& p2, MyWindow* window);

int main()
{
	MyWindow* window = MyWindow::Instance();
	double t = 0.0;
	double dt = 1 / 60.0;
	gameState currentState = MAINMENU;
	int winner = -1;

	window->setWindowSize(1366, 768);
	window->setWindowTitle("High-Speed Jousting Fights");

	soundManager.addSound("backgroundMusic", "./sounds/background.mp3", soundType::BACKGROUND);
	soundManager.addSound("randomEffect", "./sounds/effect.wav", soundType::SOUNDEFFECT);
	
	Background back("./sprites/backgrounds/back_cave.png");
	back.setSize(window->getWindowWidth(), window->getWindowHeight());

	Player p1, p2;
	initPlayers(p1, p2, window);
	Menu mainMenu, gameOver;
	mainMenu.addButton("Play", window->getWindowWidth() / 2 - (100), window->getWindowHeight() / 2, 0, 0);
	//mainMenu.addButton("Credits", window->getWindowWidth() / 2 - 100, window->getWindowHeight() / 2 + 100, 0, 0);
	mainMenu.back.setSpritePath("./sprites/backgrounds/mainMenu.png");
	mainMenu.setButtonSprite("Play", "./sprites/buttons/playUp.png");
	//mainMenu.setButtonSprite("Credits", "./sprites/buttons/creditsUp.png");
	mainMenu.setButtonClickFunction("Play", [&]() {currentState = PLAY; initPlayers(p1, p2, window); soundManager.playSound("backgroundMusic");});

	gameOver.back.setSpritePath("./sprites/backgrounds/back_cave.png");
	gameOver.addButton("Restart", window->getWindowWidth() / 2 - 100, window->getWindowHeight() / 2, 0, 0);
	gameOver.setButtonSprite("Restart", "./sprites/buttons/restartUp.png");
	gameOver.setButtonClickFunction("Restart", [&]() {currentState = MAINMENU; });

	gameOver.addButton("Nothing", window->getWindowWidth() / 2 - 150, 100, 0, 0);
	gameOver.setButtonClickFunction("Nothing", [&]() {auto s = ""; });
	window->addKeyCallbackFunction([&](int a, int b, int c, int d) {
		p1.keyCallback(a, b, c, d); 
		p2.keyCallback(a, b, c, d);
		keyHandler(a, b, c, d);
	});
	window->addMouseButtonCallbackFunction([&](int a, int b, int c, glm::vec2 d) {
		mainMenu.mouseButton(a, b, c, d);
		gameOver.mouseButton(a, b, c, d);
	});
	double currentTime = glfwGetTime();
	double newTime, frameTime;
	soundManager.setVolume(soundType::BACKGROUND, .25);
	soundManager.setVolume(soundType::SOUNDEFFECT, .25);
	p1.sm = &soundManager;
	p2.sm = &soundManager;

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		glfwPollEvents();
		
		newTime = glfwGetTime();
		frameTime = newTime - currentTime;
		currentTime = newTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		switch (currentState)
		{
		case MAINMENU:
			mainMenu.draw();
			mainMenu.shouldCheckForMouse = true;
			gameOver.shouldCheckForMouse = false;
			glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case PLAY:
			mainMenu.shouldCheckForMouse = false;
			gameOver.shouldCheckForMouse = false;
			//glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			back.draw();
			p1.draw();
			p2.draw();
			while (frameTime > 0.0)
			{
				float deltaTime = std::min(frameTime, dt);
				//std::cout << "p1 ";
				p1.update(t, deltaTime);
				p2.update(t, deltaTime);
				frameTime -= deltaTime;
				t += deltaTime;
			}
			p1.checkForPlayerCollision(p2);
			p2.checkForPlayerCollision(p1);
			if (p1.playerHealth.getCurrentHealth() == 0)
			{
				currentState = GAMEOVER;
				winner = 1;
			}
			else if (p2.playerHealth.getCurrentHealth() == 0)
			{
				currentState = GAMEOVER;
				winner = 0;
			}
			break;
		case GAMEOVER:
			if (winner == 0)
			{
				gameOver.setButtonSprite("Nothing", "./sprites/p1Winner.png");
			}
			else if (winner == 1)
			{
				gameOver.setButtonSprite("Nothing", "./sprites/p2Winner.png");
			}
			mainMenu.shouldCheckForMouse = false;
			gameOver.shouldCheckForMouse = true;
			soundManager.stopSound("backgroundMusic");
			gameOver.draw();
			break;
		}
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

void initPlayers(Player& p1, Player& p2, MyWindow* window)
{
	p1.playerHealth.reset();
	p1.rotationAngle = 0;
	p2.rotationAngle = 0;
	p2.playerHealth.reset();
	p1.setSpritePath("./sprites/red2x.png");
	p2.setSpritePath("./sprites/purple2x.png");
	p1.setPosition(0, window->getWindowHeight() - p1.getSize().y);
	p2.setSize(-1, 0);
	p2.setPosition(window->getWindowWidth() - p2.getSize().x, window->getWindowHeight() - 88);
	p2.playerHealth.healthYOffset = window->getWindowWidth() - (32 * 3);
	  
	p2.setButton(BUTTON_RIGHT, GLFW_KEY_RIGHT);
	p2.setButton(BUTTON_LEFT, GLFW_KEY_LEFT);
	p2.setButton(BUTTON_UP, GLFW_KEY_DOWN);
	p2.setButton(BUTTON_DOWN, GLFW_KEY_UP);
}