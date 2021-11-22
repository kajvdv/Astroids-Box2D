#include "Box.h"

void Box::OnCreate()
{
	world = new b2World(b2Vec2(0, 0));

	cam = b2Vec2(0, 0);

	b2BodyDef groundDef;
	groundDef.position = b2Vec2(1080 / 2, 1);
	b2PolygonShape groundShape;
	groundShape.SetAsBox(1080, 1);
	//b2Body* groundBody = world->CreateBody(&groundDef);
	//b2Fixture* fix = groundBody->CreateFixture(&groundShape, 0);

	b2BodyDef celDef;
	celDef.position = b2Vec2(1080 / 2, 720 / 10);
	b2PolygonShape celShape;
	celShape.SetAsBox(1080, 1);
	//b2Body* celBody = world->CreateBody(&celDef);
	//b2Fixture* vix = celBody->CreateFixture(&celShape, 0);

	ship = new Ship((float)(1080 / 2 / 10), (float)(720 / 2 / 10), world, this);
	listeners.push_back(ship);
}

void Box::OnInput(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		CreatePolyGon(e.button.x, e.button.y);
	}
	if (e.type == SDL_KEYDOWN)
	{
		for (KeyListener* k : listeners)
		{
			k->onKeyDown(e.key);
		}
	}
	if (e.type == SDL_KEYUP)
	{
		for (KeyListener* k : listeners)
		{
			k->onKeyUp(e.key);
		}
	}
}

void Box::OnUpdate()
{
	std::vector<b2Vec2> oldVelocities;
	for (b2Body* bullet : bullets)
	{
		oldVelocities.push_back(bullet->GetLinearVelocity());
	}
	world->Step(0.01f, 6, 3);
	b2Body* body = world->GetBodyList();
	while (body != nullptr)
	{
		if (body->GetTransform().p.y < -510)
		{
			float x = body->GetTransform().p.x;
			float angle = body->GetTransform().q.GetAngle();
			body->SetTransform(b2Vec2(x, 510), angle);
		}
		if (body->GetTransform().p.y > 580)
		{
			float x = body->GetTransform().p.x;
			float angle = body->GetTransform().q.GetAngle();
			body->SetTransform(b2Vec2(x, -580), angle);
		}
		if (body->GetTransform().p.x > 510)
		{
			float y = body->GetTransform().p.y;
			float angle = body->GetTransform().q.GetAngle();
			body->SetTransform(b2Vec2(-510, y), angle);
		}
		if (body->GetTransform().p.x < -510)
		{
			float y = body->GetTransform().p.y;
			float angle = body->GetTransform().q.GetAngle();
			body->SetTransform(b2Vec2(510, y), angle);
		}
		body = body->GetNext();
	}
	// checking if bullets have collided
	std::vector<b2Body*> newBullets;
	for (auto i = 0; i < oldVelocities.size(); i++)
	{
		if (oldVelocities[i] == bullets[i]->GetLinearVelocity())	
		{
			newBullets.push_back(bullets[i]);
		}
		else
		{
			world->DestroyBody(bullets[i]);
		}
	}
	bullets = newBullets;
	ship->OnUpdate();
}

void Box::OnRender()
{
	cam = ship->GetBody()->GetTransform().p;
	cam.x -= 108 / 2;
	cam.y -= 72 / 2;
	b2Body* body = world->GetBodyList();
	int bodyCount = world->GetBodyCount();
	SDL_Point points[8];
	for (int i = 0; i < bodyCount; i++)
	{
		int c = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_count;
		for (int i = 0; i < c; i++)
		{
			float x = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i].x;
			float y = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i].y;
			b2Vec2 worldPosition = body->GetWorldPoint(b2Vec2(x, y));
			points[i].x = (worldPosition.x - cam.x) * 10;
			points[i].y = (worldPosition.y - cam.y) * -10 + 720;
		}
		loop->DrawShape(points, c);
		body = body->GetNext();
	}
}

void Box::CreateBox(int mouseX, int mouseY)
{
	// van pixel naar meter
	float worldX = mouseX / 10 + cam.x;
	float worldY = (720 - mouseY) / 10 + cam.y;
	// b2Body aanmaken en toevoegen aan wereld
	b2BodyDef def;
	def.position = b2Vec2(worldX, worldY);
	def.type = b2_dynamicBody;
	b2PolygonShape shape;
	shape.SetAsBox(1, 1);
	b2Body* body = world->CreateBody(&def);
	b2Fixture* fix = body->CreateFixture(&shape, 1);
	//body->SetLinearVelocity(b2Vec2(1*world->GetBodyCount(), 0));
}

void Box::CreatePolyGon(int mouseX, int mouseY)
{
	float worldX = mouseX / 10 + cam.x;
	float worldY = (720 - mouseY) / 10 + cam.y;

	b2BodyDef def;
	def.position = b2Vec2(worldX, worldY);
	def.type = b2_dynamicBody;
	b2Body* body = world->CreateBody(&def);
	b2PolygonShape shape;

	b2Vec2 lowerBound(-8.0f, -8.0f);
	b2Vec2 upperBound(8.0f, 8.0f);

	b2Vec2 points[8];
	for (int32 i = 0; i < 8; ++i)
	{
		float x = 5.0f * RandomFloat();
		float y = 5.0f * RandomFloat();

		// Clamp onto a square to help create collinearities.
		// This will stress the convex hull algorithm.
		b2Vec2 v(x, y);
		v = b2Clamp(v, lowerBound, upperBound);
		points[i] = v;
	}
	shape.Set(points, 8);
	body->CreateFixture(&shape, 1);
}