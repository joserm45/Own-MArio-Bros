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

	collider = App->collision->AddCollider({ (int)position.x,(int)position.y,GOOMBA_WIDTH,GOOMBA_HEIGHT }, COLLIDER_GOOMBA, this);
	head_collider = App->collision->AddCollider({ (int)position.x + 2, (int)position.y - 2, 17, HEAD_HIGHT_SIZE }, COLLIDER_HEAD, this);
	return ret;
}

bool Enemy_Goomba::Start()
{
	
	//load texture
	text_goomba = App->tex->Load("textures/mario.png");

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
			position.y += 150.0f * dt;
		}
		//check hit for death 
		if (App->scene->god_mode == false)
		{
			if (collider->CheckCollision(App->entity_manager->player->collider->rect) == true)
			{
				App->entity_manager->player->dead = true;
				//head_collider->to_delete = true;
			}
		}
		if (head_collider->CheckCollision(App->entity_manager->player->collider->rect) == true)
		{
			
			//collider->to_delete = true;
			dead = true;
			//head_collider->to_delete = true;

			//audio of goomba death
			App->audio->PlayFx(2);
			App->entity_manager->player->jumping = true;
			App->entity_manager->player->jump_height = App->entity_manager->player->position.y - 20;
			App->entity_manager->player->jump2_on = true;
			App->entity_manager->player->score += 100;
		}
	
	}


	if (collider != NULL)
	collider->SetPos(position.x, position.y + HEAD_HIGHT_SIZE);
	if (head_collider != NULL)
	head_collider->SetPos(position.x + HEAD_WITH_SIZE, position.y -2);

	if (dead == true)
	{
		entity_state = DIE;
		CleanUp();
	}

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

	if (dead == true)
	{
		App->entity_manager->DestroyEntity(this);
	}
	return ret;
}

bool Enemy_Goomba::CleanUp()
{
	bool ret = true;
	
	collider->to_delete = true;
	head_collider->to_delete = true;
	SDL_DestroyTexture(text_goomba);
	
	/*for (uint i = 0; i < App->entity_manager->entities.count(); i++)
	{
		if (App->entity_manager->entities[i]->entity_state == DIE)
		{
			delete[]App->entity_manager->entities[i];
		}
	}*/
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

		case MOVE_RIGHT:
			current = &goomba_walk;
			break;

		case MOVE_LEFT:
			current = &goomba_walk;
			break;

		case DIE:
			current = &goomba_dead;
			break;
	}
}

void Enemy_Goomba::Move(float dt)
{
	
	if (position.x > App->entity_manager->player->position.x && position.x - App->entity_manager->player->position.x <200)
	{
		entity_state = MOVE_LEFT;
		if (App->map->Walkability(this) == true)
		{
			position.x -= 20.0f * dt;
		}

	}
	else if (position.y > App->entity_manager->player->position.y && position.x - App->entity_manager->player->position.x <200)
	{
		entity_state = MOVE_RIGHT;
		if (App->map->Walkability(this) == true)
		{
			position.x += 20.0f * dt;
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