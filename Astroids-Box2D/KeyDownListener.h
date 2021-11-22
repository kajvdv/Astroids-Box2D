#pragma once
#include <SDL.h>

class KeyListener
{
public:
	virtual void onKeyDown(SDL_KeyboardEvent e) = 0;
	virtual void onKeyUp(SDL_KeyboardEvent e) = 0;
};

