#ifndef DOOMENGINE_H
#define DOOMENGINE_H

#include <iostream>
#include "SDL.h"
#include "WADLoader.h"
#include "Map.h"
#include "Player.h"

class DoomEngine
{
private:
	int m_RenderWidth{};
	int m_RenderHeight{};

	bool m_IsRunning{};

	WADLoader m_WADLoader;
	Map* m_pMap{};
	Player* m_pPlayer{};

	SDL_Renderer* m_pRenderer{};
public:
	DoomEngine(SDL_Renderer* renderer);
	~DoomEngine();

	bool init();

	void quit();

	void handleKeys(const Uint8* keyState);

	void update();

	void render();

	bool isRunning();

	int getRenderWidth();
	int getRenderHeight();

	std::string getCurrentMapName();
	std::string getWADFileName();
};

#endif

