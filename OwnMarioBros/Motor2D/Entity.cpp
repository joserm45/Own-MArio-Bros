#include "Entity.h"
#include "j1App.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "j1Player.h"
#include "Enemy_Goomba.h"

Entity::Entity(float x, float y) : position(x, y)
{

}

Entity::~Entity()
{

}

const Collider* Entity::GetCollider() const
{
	return collider;
}

bool Entity::Update(float dt)
{
	bool ret = true;

	return ret;
}

void Entity::Draw()
{

}

bool Entity::Save(pugi::xml_node&) const
{
	bool ret = true;

	return ret;
}

bool Entity::Load(pugi::xml_node&)
{
	bool ret = true;

	return ret;
}

void Entity::LoadAnimation()
{

}

void Entity::Input(float dt)
{

}

void Entity::OnCollision(Collider* a, Collider* b)
{

}