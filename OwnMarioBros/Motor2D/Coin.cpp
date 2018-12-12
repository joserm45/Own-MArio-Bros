#include "Coin.h"
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

Coin::Coin() : Entity()
{
	name.create("coin");

	LoadAnimation();

}

// Destructor
Coin::~Coin()
{

}

// Called before render is available
bool Coin::Awake()
{
	entity_state = IDLE;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, COIN_WIDTH, COIN_HEIGHT }, COLLIDER_ITEM, this);
	return true;
}

bool Coin::Start()
{
	text_coin = App->tex->Load("textures/mario.png");

	coin_quadrant_1.x = position.x / TILE_WIDTH;
	coin_quadrant_2.x = (position.x + COIN_WIDTH) / TILE_WIDTH;

	coin_quadrant_1.y = position.y / TILE_WIDTH;
	coin_quadrant_2.y = (position.y + COIN_HEIGHT) / TILE_WIDTH;

	return true;
}

bool Coin::PreUpdate()
{
	return true;
}


bool Coin::Update(float dt)
{
	

	if (dead != true)
	{
		if (collider->CheckCollision(App->entity_manager->player->collider->rect) == true)
		{
			num_coins + 1;
			dead = true;
		}
	}

	if (collider != NULL)
		collider->SetPos(position.x, position.y);

	if (dead == true)
	{
		CleanUp();
	}

	return true;
}
bool Coin::PostUpdate()
{
	Draw();
	App->render->Blit(text_coin, position.x, position.y, &current->GetCurrentFrame());

	if (dead == true)
	{
		App->entity_manager->DestroyEntity(this);
	}
	
	return true;
}
void Coin::LoadAnimation()
{
	idle.PushBack({ 160,176,16,16 });
	idle.PushBack({ 176,176,16,16 });
	idle.PushBack({ 192,176,16,16 });
	idle.PushBack({ 208,176,16,16 });
	idle.speed = ANIMATION_SPEED;
}

void Coin::Draw()
{
	switch (entity_state)
	{
	case IDLE:
		current = &idle;
		break;
	}
}

// Called before quitting
bool Coin::CleanUp()
{
	collider->to_delete = true;
	SDL_DestroyTexture(text_coin);
	return true;
}
