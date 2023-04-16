#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "DoomEngine.h"
#include <iostream>
#include <string>

class Game
{
private:
	int m_WindowWidth{};
	int m_WindowHeight{};

	SDL_Window* m_pWindow{};
	SDL_Renderer* m_pRenderer{};
	SDL_Event m_Event{};

	DoomEngine* m_pDoomEngine{};

	int m_CurrentTime{};
	int m_PreviousTime{};
	double m_DeltaTime{};

public:
	Game(int width, int height);
	~Game();

	bool init();			// Initialize all the variables necessary for rendering using SDL plus the Doom Engine

	bool isRunning();		// Checks whether the game is still running

	void handleInput();		// Sends input to the Doom Engine
	
	void update();			// Calls the Doom Engine update function and also updates the framerate
	
	void render();			// Calls the Doom Engine render function and presents the renderer to the screen

	void delay(int ms);
};

#endif

