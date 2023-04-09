#include "DoomEngine.h"

DoomEngine::DoomEngine()
	:m_RenderWidth{ 320 }, m_RenderHeight{ 200 }, m_IsRunning{ true }, m_WADLoader{ "DOOM.WAD" }
{
	m_pMap = new Map("E1M1");
}

DoomEngine::~DoomEngine()
{
	delete m_pMap;
}

bool DoomEngine::init()
{
	m_WADLoader.load();
	m_WADLoader.loadMapData(*m_pMap);
	return true;
}

void DoomEngine::quit()
{
	m_IsRunning = false;
}

void DoomEngine::handleKeys(const Uint8* keyState)
{

}



void DoomEngine::update()
{

}

void DoomEngine::render(SDL_Renderer* renderTarget)
{
	SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
	SDL_RenderClear(renderTarget);

	m_pMap->renderAutomap(renderTarget);

	SDL_RenderPresent(renderTarget);
}

bool DoomEngine::isRunning() { return m_IsRunning; }

int DoomEngine::getRenderWidth() { return m_RenderWidth; }
int DoomEngine::getRenderHeight() { return m_RenderHeight; }

std::string DoomEngine::getCurrentMapName() { return m_pMap->getMapName(); }
std::string DoomEngine::getWADFileName() { return "DOOM.WAD"; }