#pragma once
#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "j1App.h"
#include "p2Point.h"
#include "j1Collision.h"


struct SDL_Texture;

enum ENTITY_TYPE
{
	PLAYER,
	GOOMBA,
	TURTLE,
	UNKNOWN
};

enum ENTITY_STATE
{
	IDLE,
	LEFT,
	RIGHT,
	MOVE,
	JUMP,
	DUCK,
	DIE,
	WIN,
	NO_ANIMATION
};


class Entity
{
public:

	Entity()
	{

	};
	virtual ~Entity()
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
		return this->position;
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


	ENTITY_STATE				entity_state;

	Collider*					collider = nullptr;
	Collider*					head_collider = nullptr;
};


#endif // !ENTITY_MANAGER_H_

