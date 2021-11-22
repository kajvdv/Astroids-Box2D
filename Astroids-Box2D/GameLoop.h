#pragma once
#include <SDL.h>
#include <iostream>

class GameLoop;

class Game
{
public:
	GameLoop* loop;

	virtual void OnCreate() = 0;
	virtual void OnInput(SDL_Event& e) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
};

class GameLoop
{
public:
	GameLoop(Game* game);

	void StartLoop();
	void DrawShape(SDL_Point points[], int count);
private:
	Game* game;

	bool running;
	SDL_Event e;
	int lastTime;
	int currentTime;
	int deltaTime;
	int lag;

	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Window* window;
};

