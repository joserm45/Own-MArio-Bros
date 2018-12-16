#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	
	// Destructor
	virtual ~j1Scene();

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

public:
	pugi::xml_document config;
	uint current_lvl = 1;

	//audio
	uint death_sound = 0;
	uint level_sound = 0;

	uint coin_sound = 0;
	uint click_sound = 0;
	uint pause_sound = 0;

	void LoadLevel(int level);
	bool Save(pugi::xml_node&)const;
	bool Load(pugi::xml_node&);

	bool start_scene = false;
	//bool saved = false;
	bool scene_menu = false;
	bool in_game = false;
	bool god_mode = false;

	float current_time = 0;
	float init_time = 0;



private:
};

#endif // __j1SCENE_H__