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
#include "j1EntityManager.h"
#include "Brofiler\Brofiler.h"

Enemy_Goomba::Enemy_Goomba() : Entity()
{
	name.create("goomba");

	LoadAnimation();

}

Enemy_Goomba::~Enemy_Goomba()
{

}

bool Enemy_Goomba::Awake()
{
	bool ret = true;
	entity_state = IDLE;

	return ret;
}

bool Enemy_Goomba::Start()
{
	
	//load texture
	text_goomba = App->tex->Load("textures/mario.png");

	collider = App->collision->AddCollider({ (int)position.x,(int)position.y,GOOMBA_WIDTH,GOOMBA_HEIGHT }, COLLIDER_GOOMBA, this);
	head_collider = App->collision->AddCollider({ (int)position.x + 3, (int)position.y - 2, 12, HEAD_HIGHT_SIZE }, COLLIDER_HEAD, this);
	
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
		Move(dt);
		if (Falling() == true)
		{
			position.y += 50.0f * dt;
		}
		//check hit for death 
		if (collider->CheckCollision(App->entity_manager->player->collider->rect) == true)
		{
			head_collider->to_delete = true;
			App->entity_manager->player->dead = true;
		}
		if (head_collider->CheckCollision(App->entity_manager->player->collider->rect) == true)
		{
			collider->to_delete = true;
			dead = true;
			
		}
	}
	if (dead == true)
	{
		entity_state = DIE;
	}

	collider->SetPos(position.x, position.y + HEAD_HIGHT_SIZE);
	head_collider->SetPos(position.x + HEAD_WITH_SIZE, position.y);
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

	collider->to_delete = true;
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
	switch (entity_state)
	{
		case IDLE:
			current = &goomba_idle;
			break;

		case MOVE:
			current = &goomba_walk;
			break;

		case RIGHT:
			current = &goomba_walk;
			break;
		case LEFT:
			current = &goomba_walk;
			break;

		case DIE:
			current = &goomba_dead;
			break;
	}
}

void Enemy_Goomba::Move(float dt)
{
	
	if (position.x > App->entity_manager->player->position.x && position.x - App->entity_manager->player->position.x <500)
	{
		entity_state = MOVE;
		if (App->map->Walkability(this) == true)
		{
			position.x -= 15.0f * dt;
		}

	}
	else if (position.y > App->entity_manager->player->position.y && position.x - App->entity_manager->player->position.x <500)
	{
		entity_state = MOVE;
		if (App->map->Walkability(this) == true)
		{
			position.x += 15.0f * dt;
		}
	}
	
	
	/*//just to check if animation works
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		position.x += GOOMBA_SPEED;
		entity_state = MOVE;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		entity_state = DIE;
	}*/
}

bool Enemy_Goomba::Falling()
{
	bool ret = false;
	if (entity_state != WIN)
	{
		p2List_item<Layer*>* iterator;
		p2List_item<Layer*>* layer = nullptr;

		for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
		{
			if (iterator->data->name == "logic")
			{
				layer = iterator;
			}
		}

		//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
		uint* nextGid1 = &layer->data->gid[goomba_quadrant_1.x + goomba_quadrant_2.y * layer->data->width];
		uint* nextGid2 = &layer->data->gid[goomba_quadrant_2.x + goomba_quadrant_2.y * layer->data->width];


		if (*nextGid1 != 650 && *nextGid2 != 650)
		{
			ret = true;
		}
		if (*nextGid1 == 679 || *nextGid2 == 679)
		{
			dead = true;
		}
	}
	return ret;
}