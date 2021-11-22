#pragma once
#include <vector>
#include <SDL.h>
#include <box2d.h>
#include "GameLoop.h"
#include "KeyDownListener.h"
#include "Ship.h"

class Ship;

class Box :
	public Game
{
public:
	std::vector<b2Body*> bullets;
private:
	b2World* world;
	Ship* ship;
	b2Vec2 cam;
	std::vector<KeyListener*> listeners;

	virtual void OnCreate() override;
	virtual void OnInput(SDL_Event& e) override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	void CreateBox(int mouseX, int mouseY);
	void CreatePolyGon(int mouseX, int mouseY);

	inline float RandomFloat()
	{
		float r = (float)(rand() & (32767));
		r /= 32767;
		r = 2.0f * r - 1.0f;
		return r;
	}
};

