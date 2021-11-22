#include "Ship.h"

Ship::Ship(float WorldX, float WorldY, b2World* world, Box* game)
{
	verticesCount = 3;
	rotationSpeed = 0;
	acc = false;
	left = false;
	right = false;
	stop = false;
	space = false;
	shot = false;
	b2BodyDef def;
	def.position = b2Vec2(WorldX, WorldY);
	def.type = b2_dynamicBody;
	b2PolygonShape shape;
	b2Vec2 vertices[8];
	vertices[0].Set(0, 1);
	vertices[1].Set(1, -1);
	vertices[2].Set(-1, -1);
	shape.Set(vertices, 3);
	body = world->CreateBody(&def);
	body->CreateFixture(&shape, 10);
	this->world = world;
	this->game = game;
}

void Ship::onKeyDown(SDL_KeyboardEvent e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		acc = true;
		break;
	case SDLK_LEFT:
		left = true;
		break;
	case SDLK_RIGHT:
		right = true;
		break;
	case SDLK_DOWN:
		stop = true;
		break;
	case SDLK_SPACE:
		space = true;
		break;
	}
}

void Ship::onKeyUp(SDL_KeyboardEvent e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		acc = false;
		break;
	case SDLK_LEFT:
		left = false;
		break;
	case SDLK_RIGHT:
		right = false;
		break;
	case SDLK_DOWN:
		stop = false;
		break;
	case SDLK_SPACE:
		space = false;
		shot = false;
		break;
	}
}

void Ship::OnUpdate()
{
	if (acc)
	{
		b2Vec2 dir = body->GetTransform().q.GetYAxis();
		b2Vec2 pos = body->GetTransform().p;
		dir.x *= 1000;
		dir.y *= 1000;
		body->ApplyForce(dir, pos, true);
	}
	if (right)
	{
		float angle = body->GetTransform().q.GetAngle();
		b2Vec2 pos = body->GetTransform().p;
		body->SetTransform(pos, angle - 0.05f);
	}
	if (left)
	{
		float angle = body->GetTransform().q.GetAngle();
		b2Vec2 pos = body->GetTransform().p;
		body->SetTransform(pos, angle + 0.05f);
	}
	if (stop)
	{
		float m = body->GetLinearVelocity().Length();
		if (m != 0)
		{
			b2Vec2 v = body->GetLinearVelocity();
			v.x /= m;
			v.y /= m;
			b2Vec2 dir(v.x * -400, v.y * -400);
			b2Vec2 pos = body->GetTransform().p;
			body->ApplyForce(dir, pos, true);
		}
	}
	if (left || right || stop) body->SetAngularVelocity(0);
	if (space && shot == false)
	{
		shot = true;
		b2BodyDef def;
		def.type = b2_dynamicBody;
		def.bullet = true;
		def.position = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[1];
		def.position = body->GetWorldPoint(def.position);
		b2Vec2 offset = body->GetTransform().q.GetYAxis();
		def.position += offset;
		def.linearVelocity = offset;
		def.linearVelocity *= 200;
		b2Body* bullet = world->CreateBody(&def);
		b2PolygonShape shape;
		shape.SetAsBox(0.1f, 0.1f);

		bullet->CreateFixture(&shape, 40);
		game->bullets.push_back(bullet);
	}
}