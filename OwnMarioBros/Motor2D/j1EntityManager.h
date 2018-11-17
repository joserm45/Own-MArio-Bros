#pragma once
#ifndef __j1ENTITY_MANAGER_H__
#define __j1ENTITY_MANAGER_H__

#include "j1Module.h"
#include "p2List.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "Entity.h"
#include "j1Player.h"
#include "Enemy_Boo.h"
#include "Enemy_Goomba.h"


class j1EntityManager : public j1Module
{
public:
	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

	void OnCollision(Collider* a, Collider* b);

	//Entity* CreateEntity(ENTITY_TYPE type);
	void DestroyEntity(Entity* entity);

public:
	p2List<Entity*>		entities;

	j1Player*			player = nullptr;
	j1Collision*		collider = nullptr;
};


#endif // !_j1ENTITYMANAGER_H_
