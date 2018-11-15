#ifndef __ENTITY_MANAGER_H_
#define __ENTITY_MANAGER_H_

#include "j1App.h"
#include "p2Point.h"
#include "j1Collision.h"


struct SDL_Texture;

enum ENTITY_TYPE
{
	PLAYER,
	GOOMBA,
	TURTLE,
	ERROR
};

enum ENTITY_STATE
{
	IDLE,
	LEFT,
	RIGHT,
	DIE
};


class EntityManager
{
public:

	EntityManager()
	{

	};
	virtual ~EntityManager()
	{

	};

	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	fPoint	GetPos() const
	{
		return position;
	}


	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&)const
	{
		return true;
	}

	virtual void OnCollision(Collider* a, Collider* b)
	{

	}

public:

	ENTITY_TYPE					entity_type;
	p2SString					name;
	fPoint						position;


	ENTITY_STATE				state;

	Collider*					collision = nullptr;

};


#endif // !ENTITY_MANAGER_H_

