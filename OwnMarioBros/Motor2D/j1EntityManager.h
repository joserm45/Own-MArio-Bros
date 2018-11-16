#ifndef _j1ENTITYMANAGER_H_
#define _j1ENTITYMANAGER_H_

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "p2DynArray.h"
#include "Entity.h"

enum ENTITY_TYPE
{
	PLAYER,
	GOOMBA,
	TURTLE,
	NO
};

enum ENTITY_STATE
{
	IDLE1,
	LEFT1,
	RIGHT1,
	JUMP1,
	DUCK1,
	DIE1,
	WIN1
};

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
	p2DynArray<Entity*> entities;
	ENTITY_TYPE entity_type;
	ENTITY_STATE entity_state;
};


#endif // !_j1ENTITYMANAGER_H_
