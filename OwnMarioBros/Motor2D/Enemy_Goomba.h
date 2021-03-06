#pragma once
#ifndef __ENEMY_GOOMBA_H__
#define __ENEMY_GOOMBA_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "Animation.h"
#include "j1EntityManager.h"
#include "Entity.h"

#define GOOMBA_SPEED 1.5f
#define ANIMATION_SPEED 0.145f
#define GOOMBA_HEIGHT 16
#define GOOMBA_WIDTH 16
#define TILE_WIDTH 16
#define TiLE_HEIGHT 16
#define HEAD_HIGHT_SIZE 4
#define HEAD_WITH_SIZE 0

/*enum STATUS_GOOMBA
{
	IDLE_GOOMBA,
	MOVE_GOOMBA,
	DIE_GOOMBA
};*/

class Enemy_Goomba : public Entity
{
public:
	Enemy_Goomba();
	virtual ~Enemy_Goomba();

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
	void Move(float dt);
	bool Falling();

public:

	iPoint				goomba_quadrant_1;
	iPoint				goomba_quadrant_2;

	//STATUS_GOOMBA status;
	bool moving = false;

private:
	SDL_Texture * text_goomba = nullptr;

	bool dead = false;

	//Animations
	Animation goomba_idle;
	Animation goomba_walk;
	Animation goomba_dead;
	Animation* current = nullptr;



};

#endif
