#pragma once
#ifndef __ENEMY_BOO_H__
#define __ENEMY_BOO_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "Animation.h"
#include "j1EntityManager.h"
#include "Entity.h"

#define BOO_SPEED 1.5f
#define ANIMATION_SPEED 0.145f
#define BOO_HEIGHT 16
#define BOO_WIDTH 16
#define TILE_WIDTH 16
#define TiLE_HEIGHT 16

/*enum STATUS_BOO
{
	IDLE_BOO,
	LEFT_BOO,
	RIGHT_BOO,
	DIE_BOO
};*/

class Enemy_Boo : public Entity
{
public:
	Enemy_Boo();
	virtual ~Enemy_Boo();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	//bool Save(pugi::xml_node&) const;
	//bool Load(pugi::xml_node&);

	void LoadAnimation();
	void Draw();
	void Move();

public:

	iPoint				boo_quadrant_1;
	iPoint				boo_quadrant_2;

	//STATUS_BOO status;
	bool moving = false;

private:
	SDL_Texture * text_boo = nullptr;

	bool dead = false;

	//Animations
	Animation boo_idle;
	Animation boo_left;
	Animation boo_right;
	Animation boo_dead;
	Animation* current = nullptr;

	//Collider
	
	Collider* quadrant1 = nullptr;
	Collider* quadrant2 = nullptr;

};

#endif
