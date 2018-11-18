#include "Enemy_Boo.h"
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

Enemy_Boo::Enemy_Boo() : Entity()
{
	name.create("boo");

	LoadAnimation();

}

Enemy_Boo::~Enemy_Boo()
{

}

bool Enemy_Boo::Awake()
{
	bool ret = true;
	entity_state = IDLE;

	return ret;
}

bool Enemy_Boo::Start()
{
	

	//load texture
	text_boo = App->tex->Load("textures/mario.png");

	collider_boo = App->collision->AddCollider({ (int)position.x,(int)position.y,BOO_WIDTH,BOO_HEIGHT }, COLLIDER_BOO, this);

	boo_quadrant_1.x = position.x / TILE_WIDTH;
	boo_quadrant_2.x = (position.x + BOO_WIDTH) / TILE_WIDTH;

	boo_quadrant_1.y = position.y / TILE_WIDTH;
	boo_quadrant_2.y = (position.y + BOO_HEIGHT) / TILE_WIDTH;

	return true;

}

bool Enemy_Boo::PreUpdate()
{
	BROFILER_CATEGORY("BooPreUpdate", Profiler::Color::Peru);
	bool ret = true;

	return ret;
}

bool Enemy_Boo::Update(float dt)
{
	BROFILER_CATEGORY("BooUpdate", Profiler::Color::IndianRed);
	bool ret = true;

	if (dead != true)
	{
		Move();
		//check hit for death 
	}
	if (dead == true)
	{
		entity_state = DIE;
	}

	collider_boo->SetPos(position.x, position.y);

	return ret;
}

bool Enemy_Boo::PostUpdate()
{
	BROFILER_CATEGORY("BooPostUpdate", Profiler::Color::Gainsboro);
	bool ret = true;

	Draw();
	//Blit player
	App->render->Blit(text_boo, position.x, position.y, &current->GetCurrentFrame());

	boo_quadrant_1.x = position.x / TILE_WIDTH;
	boo_quadrant_2.x = (position.x + BOO_WIDTH) / TILE_WIDTH;

	boo_quadrant_1.y = position.y / TILE_WIDTH;
	boo_quadrant_2.y = (position.y + BOO_HEIGHT) / TILE_WIDTH;

	return ret;
}

bool Enemy_Boo::CleanUp()
{
	bool ret = true;

	collider_boo->to_delete = true;
	SDL_DestroyTexture(text_boo);
	return ret;
}

void Enemy_Boo::LoadAnimation()
{
	boo_dead.PushBack({ 112,176,16,16 });
	boo_dead.PushBack({ 128,176,16,16 });
	boo_dead.PushBack({ 144,176,16,16 });
	boo_dead.speed = ANIMATION_SPEED;

	boo_right.PushBack({ 64,176,16,16 });
	boo_right.PushBack({ 80,176,16,16 });
	boo_right.speed = ANIMATION_SPEED;

	boo_left.PushBack({ 96,176,16,16 });
	boo_left.PushBack({ 112,176,16,16 });
	boo_left.speed = ANIMATION_SPEED;

	boo_idle.PushBack({ 96,176,16,16 });
	boo_idle.PushBack({ 112,176,16,16 });
	boo_idle.speed = ANIMATION_SPEED;
	//boo_idle.loop = 1;
}

void Enemy_Boo::Draw()
{
	switch (entity_state)
	{
	case IDLE:
		current = &boo_idle;
		break;

	case LEFT:
		current = &boo_left;
		break;

	case RIGHT:
		current = &boo_right;
		break;

	case DIE:
		current = &boo_dead;
		break;
	}
}

void Enemy_Boo::Move()
{
	entity_state = IDLE;
	//just to check if animation works
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		position.x += BOO_SPEED;
		entity_state = RIGHT;
	}

	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
	{
		position.x -= BOO_SPEED;
		entity_state = LEFT;
	}
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		position.y += BOO_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		position.y -= BOO_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		entity_state = DIE;
	}
}