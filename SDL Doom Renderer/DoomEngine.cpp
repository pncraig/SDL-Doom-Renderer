#include "DoomEngine.h"

DoomEngine::DoomEngine(SDL_Renderer* renderer)
	:m_pRenderer{ renderer }, m_RenderWidth { 320 }, m_RenderHeight{ 200 }, m_IsRunning{ true }, m_WADLoader{ "DOOM.WAD" }
{
	
}

DoomEngine::~DoomEngine()
{
	delete m_pMap;
	delete m_pPlayer;
}

bool DoomEngine::init()
{
	m_pPlayer = new Player(1);
	m_pMap = new Map(m_pRenderer, "E1M1", m_pPlayer);

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

void DoomEngine::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

	m_pMap->renderAutomap();

}

bool DoomEngine::isRunning() { return m_IsRunning; }

int DoomEngine::getRenderWidth() { return m_RenderWidth; }
int DoomEngine::getRenderHeight() { return m_RenderHeight; }

std::string DoomEngine::getCurrentMapName() { return m_pMap->getMapName(); }
std::string DoomEngine::getWADFileName() { return "DOOM.WAD"; }