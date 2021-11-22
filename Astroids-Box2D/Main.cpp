#include <iostream>
#include <vector>
#include <box2d.h>
#include <SDL.h>
#include "GameLoop.h"
#include "Box.h"
#include "Ship.h"

int main(int argc, char* args[])
{
	
	Box b;
	GameLoop loop(&b);
	loop.StartLoop();
	return 0;
}