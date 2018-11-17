#include "Enemy_Goomba.h"
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
#include "j1Collision.h"
#include "Brofiler\Brofiler.h"

Enemy_Goomba::Enemy_Goomba() : j1Module()
{
	name.create("goomba");

	LoadAnimation();

}

Enemy_Goomba::~Enemy_Goomba()
{

}

bool Enemy_Goomba::Awake(pugi::xml_node&)
{
	bool ret = true;
	status = IDLE_GOOMBA;

	return ret;
}

bool Enemy_Goomba::Start()
{
	position.x = 550.0f;
	position.y = 192.0f;

	//load texture
	text_goomba = App->tex->Load("textures/mario.png");

	collider_goomba = App->collision->AddCollider({ (int)position.x,(int)position.y,GOOMBA_WIDTH,GOOMBA_HEIGHT }, COLLIDER_ENEMY_NORMAL, this);

	goomba_quadrant_1.x = position.x / TILE_WIDTH;
	goomba_quadrant_2.x = (position.x + GOOMBA_WIDTH) / TILE_WIDTH;

	goomba_quadrant_1.y = position.y / TILE_WIDTH;
	goomba_quadrant_2.y = (position.y + GOOMBA_HEIGHT) / TILE_WIDTH;

	return true;

}

bool Enemy_Goomba::PreUpdate()
{
	BROFILER_CATEGORY("GoombaPreUpdate", Profiler::Color::AliceBlue);
	bool ret = true;

	return ret;
}

bool Enemy_Goomba::Update(float dt)
{
	BROFILER_CATEGORY("GoombaUpdate", Profiler::Color::AntiqueWhite);
	bool ret = true;

	if (dead != true)
	{
		Move();
		//check hit for death 
	}
	if (dead == true)
	{
		status = DIE_GOOMBA;
	}

	collider_goomba->SetPos(position.x, position.y);

	return ret;
}

bool Enemy_Goomba::PostUpdate()
{
	BROFILER_CATEGORY("GoombaPostUpdate", Profiler::Color::Aquamarine);
	bool ret = true;

	Draw();
	//Blit player
	App->render->Blit(text_goomba, position.x, position.y, &current->GetCurrentFrame());

	goomba_quadrant_1.x = position.x / TILE_WIDTH;
	goomba_quadrant_2.x = (position.x + GOOMBA_WIDTH) / TILE_WIDTH;

	goomba_quadrant_1.y = position.y / TILE_WIDTH;
	goomba_quadrant_2.y = (position.y + GOOMBA_HEIGHT) / TILE_WIDTH;

	return ret;
}

bool Enemy_Goomba::CleanUp()
{
	bool ret = true;

	collider_goomba->to_delete = true;
	SDL_DestroyTexture(text_goomba);
	return ret;
}

void Enemy_Goomba::LoadAnimation()
{
	goomba_dead.PushBack({ 0,176,16,16 });

	goomba_walk.PushBack({ 16,176,16,16 });
	goomba_walk.PushBack({ 32,176,16,16 });
	goomba_walk.speed = ANIMATION_SPEED;

	goomba_idle.PushBack({ 48,176,16,16 });
}

void Enemy_Goomba::Draw()
{
	switch (status)
	{
		case IDLE_GOOMBA:
			current = &goomba_idle;
			break;

		case MOVE_GOOMBA:
			current = &goomba_walk;
			break;

		case DIE_GOOMBA:
			current = &goomba_dead;
			break;
	}
}

void Enemy_Goomba::Move()
{
	//just to check if animation works
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		position.x += GOOMBA_SPEED;
		status = MOVE_GOOMBA;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		status = DIE_GOOMBA;
	}
}