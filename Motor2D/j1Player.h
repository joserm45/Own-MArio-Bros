#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"
#include "Animation.h"

#define PLAYER_SPEED 2
#define PLAYER_JUMP 50
#define ANIMATION_SPEED 0.045f
#define GRAVITY 1

enum STATUS
{
	IDLE,
	LEFT,
	RIGHT,
	JUMP,
	DUCK,
	DIE,
};

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

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
	void Draw();

public:
	iPoint position;
private:
	SDL_Texture * text_player = nullptr;
	//uint velocity_y = 0;
	bool moving = false;
	//bool duck = false;
	//bool air = false;
	

	//animations
	Animation right_idle;
	Animation left_idle;
	Animation move_right;
	Animation move_left;
	Animation right_jump;
	Animation left_jump;
	Animation right_duck;
	Animation left_duck;
	//Animation right_die;
	//Animation left_die;
	Animation die;
	Animation* current=nullptr;
	STATUS status;
	bool back = false;
};

#endif
