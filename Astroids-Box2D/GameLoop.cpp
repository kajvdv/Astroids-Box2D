#include "GameLoop.h"

GameLoop::GameLoop(Game* game)
{
	this->game = game;
	game->loop = this;
	
	running = true;
	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;
	lag = 0;
}

void GameLoop::StartLoop()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Astroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);
	
	game->OnCreate();

	lastTime = SDL_GetTicks();

	while (running)
	{
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lag += deltaTime;

		// Get user Input
		while (SDL_PollEvent(&e) == !0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				game->OnInput(e);
			}
		}
		// Update Game
		while (lag >= 10)
		{
			game->OnUpdate();
			lag -= 10;
		}
		// Render Game
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		game->OnRender();

		SDL_UpdateWindowSurface(window);
		lastTime = currentTime;
	}

	SDL_Quit();
}
void GameLoop::DrawShape(SDL_Point points[], int count)
{
	SDL_Point point1 = points[count - 1];
	for (int i = 0; i < count; ++i)
	{
		SDL_Point point2 = points[i];
		SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
		point1 = point2;
	}
}