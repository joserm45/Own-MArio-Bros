#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Textures.h"

#define PLAYER_SPEED 5
#define PLAYER_JUMP 8

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

	// Animation
	void Draw();

public:
	iPoint position;
private:
	SDL_Texture * graph = nullptr;
	//uint gravity = 3;
	//uint velocity = 5;

	//animations

};

#endif
