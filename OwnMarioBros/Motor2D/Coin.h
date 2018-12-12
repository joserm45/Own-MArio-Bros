#pragma once
#ifndef __COIN_H__
#define __COIN_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "Animation.h"
#include "j1EntityManager.h"
#include "Entity.h"


#define COIN_HEIGHT 12
#define COIN_WIDTH 9
#define ANIMATION_SPEED 0.165f

class Coin : public Entity
{
public:
	Coin();
	virtual ~Coin();

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

	void LoadAnimation();
	void Draw();
public:

	iPoint				coin_quadrant_1;
	iPoint				coin_quadrant_2;
	int					num_coins = 0;
private:
	bool dead = false;
	SDL_Texture * text_coin = nullptr;

	//Animations
	Animation idle;
	Animation* current = nullptr;
};








#endif