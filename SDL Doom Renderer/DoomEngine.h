#ifndef DOOMENGINE_H
#define DOOMENGINE_H

#include <iostream>
#include "SDL.h"
#include "WADLoader.h"
#include "Map.h"

class DoomEngine
{
private:
	int m_RenderWidth{};
	int m_RenderHeight{};

	bool m_IsRunning{};

	WADLoader m_WADLoader;
	Map* m_pMap{};
public:
	DoomEngine();
	~DoomEngine();

	bool init();

	void quit();

	void handleKeys(const Uint8* keyState);

	void update();

	void render(SDL_Renderer* renderTarget);

	bool isRunning();

	int getRenderWidth();
	int getRenderHeight();

	std::string getCurrentMapName();
	std::string getWADFileName();
};

#endif

