#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1EntityManager.h"
#include "j1FadeToBlack.h"
#include "j1Gui.h"

#include "Brofiler\Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	/*if (current_lvl == 1)
	{
		App->map->Load("lvl1.tmx");
		App->audio->PlayMusic("audio/music/lvl_1.ogg");

	}
	else if (current_lvl == 2)
	{
		App->map->Load("lvl2.tmx");
		App->audio->PlayMusic("audio/music/lvl_2.ogg");

	}*/

	App->audio->LoadFx("audio/music/jump.wav");
	App->audio->LoadFx("audio/music/double_jump.wav");
	death_sound = App->audio->LoadFx("audio/music/life_lost.ogg");
	level_sound = App->audio->LoadFx("audio/music/level_clear.ogg");
	//App->entity_manager->CreateEntities();
	if(scene_starts == true)
		LoadLevel(1);
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("ScenePreUpdate", Profiler::Color::Cyan);
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("SceneUpdate", Profiler::Color::BlueViolet);
	current_time += dt;
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		LoadLevel(1);
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		LoadLevel(current_lvl);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		LoadLevel(2);
	}

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		App->scene->saved = true;
		App->LoadGame();
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		App->gui->debug_UI = !App->gui->debug_UI;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		god_mode = !god_mode;

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (App->map->logic == false)
		{
			App->map->logic = true;
		}
		else if (App->map->logic == true)
		{
			App->map->logic = false;
		}
	}

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	// TODO 7: Set the window title like
	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"
	/*p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());*/
	//p2SString title("%c", *App->win->SetTitle(title.GetString()));

	//Changing Level
	if (App->map->lvl1_complete == true)
	{
		App->entity_manager->player->entity_state = WIN;
		App->audio->StopMusic();
		App->audio->PlayFx(App->scene->level_sound);
		App->entity_manager->player->moving = false;

		if (App->entity_manager->player->position.y < 169)
			App->entity_manager->player->position.y += 50 * dt;

		App->entity_manager->player->position.x += 20 * dt;

		if (App->map->init_timer == true)
		{
			init_time = current_time;
			App->map->init_timer = false;
		}
		if ((current_time - init_time * dt) >= init_time + 4.5)
		{
			LoadLevel(2);
			App->map->lvl1_complete = false;
			current_lvl = 2;
			App->entity_manager->player->entity_state = IDLE;
		}
	}

	if (App->map->lvl2_complete == true)
	{
		App->entity_manager->player->entity_state = WIN;
		App->audio->StopMusic();
		App->audio->PlayFx(App->scene->level_sound);
		App->entity_manager->player->moving = false;
		if (App->entity_manager->player->position.y < 169)
			App->entity_manager->player->position.y += 50 * dt;
		App->entity_manager->player->position.x += 20 * dt;
		if (App->map->init_timer == true)
		{
			init_time = current_time;
			App->map->init_timer = false;
		}
		if ((current_time - init_time * dt) >= init_time + 4.5)
		{
			LoadLevel(1);
			App->map->lvl2_complete = false;
			current_lvl = 1;
			App->entity_manager->player->entity_state = IDLE;
		}
	}

	if (App->entity_manager->player != NULL && App->entity_manager->player->dead == true)
	{
		App->audio->StopMusic();
		App->audio->PlayFx(App->scene->death_sound);
		App->entity_manager->player->moving = false;

		LoadLevel(current_lvl);
		App->entity_manager->player->dead = false;
		App->entity_manager->player->entity_state = IDLE;
	}
	
	if (App->want_to_load == true)
	{
		App->audio->StopMusic();
		//App->audio->PlayFx(App->scene->level_sound);
		App->entity_manager->player->moving = false;

		App->entity_manager->player->entity_state = IDLE;
		
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("ScenePostUpdate", Profiler::Color::Cyan);
	bool ret = true;
	
	/*if (App->want_to_load == true)
	{
		LoadLevel(current_lvl);
	}*/
	if (App->want_to_load == true)
	{
		App->audio->StopMusic();
		//App->audio->PlayFx(App->scene->level_sound);
		App->entity_manager->player->moving = false;

		//LoadLevel(current_lvl);

		App->entity_manager->player->entity_state = IDLE;

	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		scene_starts == true;

		//ret = false;
	}


	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::LoadLevel(int level)
{
	BROFILER_CATEGORY("LoadLevel", Profiler::Color::Navy);

	
	if (scene_starts == false)
	{
		scene_starts = true;
	}
	else
	{
		App->map->UnloadMap();
		App->fade_to_black->FadeToBlack(NULL, NULL, 1.5f);
	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	if (level == 1)
	{		
		App->map->Load("lvl1.tmx");
		App->audio->PlayMusic("audio/music/lvl_1.ogg");
		current_lvl = level;
	}
	else if (level == 2)
	{
		App->map->Load("lvl2.tmx");
		App->audio->PlayMusic("audio/music/lvl_2.ogg");
		current_lvl = level;
	}

	App->entity_manager->DestroyEntities();
	if (App->want_to_load != true)
		App->entity_manager->CreateEntities();
	//else
		
//App->entity_manager->player->collider->SetPos(App->entity_manager->player->position.x, App->entity_manager->player->position.y);
}
bool j1Scene::Save(pugi::xml_node& node)const
{
	node.append_attribute("current_lvl") = current_lvl;
	return true;
}
bool j1Scene::Load(pugi::xml_node& node)
{
	LoadLevel(node.attribute("current_lvl").as_uint());
	return true;
}
