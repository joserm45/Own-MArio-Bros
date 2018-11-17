#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "Animation.h"
#include "j1EntityManager.h"
#include "Entity.h"

#define PLAYER_SPEED 112.0f
#define PLAYER_JUMP 150.0f
#define ANIMATION_SPEED 0.165f
#define GRAVITY 1.0f
#define MARIO_HEIGHT 32
#define MARIO_HIGHT 16
#define MARIO_WIDTH 16
#define TILE_WIDTH 16
#define TiLE_HEIGHT 16

/*enum STATUS
{
	IDLE,
	LEFT,
	RIGHT,
	JUMP,
	DUCK,
	DIE,
	WIN
};*/

class j1Player : public Entity
{
public:
	j1Player();
	~j1Player();

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
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void CameraMovement();
	// Animation
	void LoadAnimation();
	void Draw();
	bool Falling();
	bool Jump();
	void Input(float dt);
	void LoadPlayerFromTiled();


public:
	
	fPoint position;

	iPoint				player_quadrant_1;
	iPoint				player_quadrant_2;

	uint count_jump = 0;
	bool moving = false;
	float current_time = 0;
	float init_time = 0;
	
	bool jumping = false;
private:
	SDL_Texture * text_player = nullptr;
	//uint velocity_y = 0;
	bool sprite_moving = false;
	
	bool jumping_over = false;
	bool dead = false;
	bool back = false;
	bool jump1_on = false;
	bool jump2_on = false;

	bool init_timer = false;

	//animations
	Animation right_idle;
	Animation left_idle;
	Animation move_right;
	Animation move_left;
	Animation right_jump;
	Animation left_jump;
	Animation right_duck;
	Animation left_duck;
	Animation die;
	Animation win;
	Animation* current = nullptr;
		//god mode
	Animation god_right_idle;
	Animation god_left_idle;
	Animation god_move_right;
	Animation god_move_left;
	Animation god_right_jump;
	Animation god_left_jump;
	Animation god_right_duck;
	Animation god_left_duck;

	uint jump_height = 0;
	
	Collider* collider_player = nullptr;
	Collider* quadrant1 = nullptr;
	Collider* quadrant2 = nullptr;
};

#endif
