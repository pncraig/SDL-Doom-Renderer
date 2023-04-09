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

	SDL_Window* m_Window{};
	SDL_Renderer* m_RenderTarget{};
	SDL_Event m_Event{};

	DoomEngine* m_pDoomEngine{};

	int m_CurrentTime{};
	int m_PreviousTime{};
	double m_DeltaTime{};

public:
	Game(int width, int height);
	~Game();

	bool init();

	bool isRunning();

	void handleInput();
	
	void update();
	
	void render();

	void delay(int ms);
};

#endif

