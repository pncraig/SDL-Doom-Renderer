#include "Game.h"

// Public
Game::Game(int width, int height)
	:m_WindowWidth{ width }, m_WindowHeight{ height }
{
}

Game::~Game()
{
	delete m_pDoomEngine;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

bool Game::init()
{
	// SDL_Init() returns a negative number upon failure, and SDL_INIT_EVERYTHING sets all the flags to true
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << '\n';	// SDL_GetError() returns information about an error that occurred in a string
		return false;
	}

	// SDL_CreateWindow() creates a window
	//								Window name	  Window X position     Window Y position   width height    flags
	//									 V			      V						V			   V    V         V
	m_pWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, 0);

	if (m_pWindow == nullptr)
	{
		std::cerr << "Error creating window: " << SDL_GetError() << '\n';
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer == nullptr)
	{
		std::cerr << "Error creating render target: " << SDL_GetError() << '\n';
		return false;
	}

	m_pDoomEngine = new DoomEngine(m_pRenderer);

	if (m_pDoomEngine == nullptr)
	{
		std::cerr << "Failed to allocate memory for the Doom Engine\n";
		return false;
	}

	// SDL_Texture* frameBuffer{ SDL_CreateTexture(renderTarget, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, m_WindowWidth, m_WindowHeight) };

	if (SDL_RenderSetLogicalSize(m_pRenderer, m_pDoomEngine->getRenderWidth(), m_pDoomEngine->getRenderHeight()) != 0)
	{
		std::cerr << "SDL failed to set logical size: " << SDL_GetError() << '\n';
		return false;
	}

	// Initialize the Doom Engine
	if (!m_pDoomEngine->init())
	{
		std::cerr << "Error initializing Doom Engine\n";
		return false;
	}

	return true;
}

bool Game::isRunning()
{
	return m_pDoomEngine->isRunning();
}

void Game::handleInput()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type)
		{
			// Check if the exit button has been clicked
		case SDL_QUIT:
			m_pDoomEngine->quit();
			break;

			// Check for window events
		case SDL_WINDOWEVENT:
			// If the window is minimized, wait for events. Fixes memory spikes
			if (ev.window.event == SDL_WINDOWEVENT_MINIMIZED)
			{
				while (SDL_WaitEvent(&ev))
				{
					if (ev.window.event == SDL_WINDOWEVENT_RESTORED)
						break;
				}
			}
			break;
		}
	}

	const Uint8* keyState{ SDL_GetKeyboardState(NULL) };
	m_pDoomEngine->handleKeys(keyState);
}

void Game::update()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = SDL_GetTicks();
	m_DeltaTime = (m_CurrentTime - m_PreviousTime) / 1000.0;

	int fps{ static_cast<int>(1.0 / m_DeltaTime) };

	std::string str{ std::to_string(fps) };
	SDL_SetWindowTitle(m_pWindow, str.c_str());

	m_pDoomEngine->update();
}

void Game::render()
{

	m_pDoomEngine->render();
	
	SDL_RenderPresent(m_pRenderer);
}

void Game::delay(int ms)
{
	SDL_Delay(10);
}