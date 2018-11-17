#include "j1EntityManager.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "Enemy_Goomba.h"
#include "Brofiler\Brofiler.h"

j1EntityManager::j1EntityManager() : j1Module()
{
	name.create("entities");

}

j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node&)
{
	bool ret = true;
	entity_state = IDLE1;
	return ret;
}

bool j1EntityManager::Start()
{
	bool ret = true;
	
	return ret;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("EntityManagerPreUpdate", Profiler::Color::Azure);
	bool ret = true;

	return ret;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("EntityManagerUpdate", Profiler::Color::Bisque);
	bool ret = true;

	return ret;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("EntityManagerPostUpdate", Profiler::Color::BlanchedAlmond);
	bool ret = true;

	return ret;
}

bool j1EntityManager::CleanUp()
{
	bool ret = true;

	return ret;
}

bool j1EntityManager::Load(pugi::xml_node&)
{
	bool ret = true;

	return ret;
}

bool j1EntityManager::Save(pugi::xml_node&)const
{
	bool ret = true;

	return ret;
}

void j1EntityManager::OnCollision(Collider* a, Collider* b)
{

}
/*
Entity* j1EntityManager::CreateEntity(ENTITY_TYPE type)
{

}
*/
void j1EntityManager::DestroyEntity(Entity* entity)
{

}