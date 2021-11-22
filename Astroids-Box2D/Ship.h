#pragma once
#include <box2d.h>
#include <SDL.h>
#include "GameLoop.h"
#include "KeyDownListener.h"
#include "Box.h"

class Box;

class Ship : public KeyListener
{
public:
	Ship(float WorldX, float WorldY, b2World* world, Box* game);
	inline b2Body* GetBody() { return body; }
	virtual void onKeyDown(SDL_KeyboardEvent e) override;
	virtual void onKeyUp(SDL_KeyboardEvent e) override;
	void OnUpdate();

private:
	int verticesCount;
	b2Body* body;
	bool acc;
	bool left;
	bool right;
	bool stop;
	bool space;
	bool shot;
	float rotationSpeed;
	b2World* world;
	Box* game;
};

