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
#include "Entity.h"
#include "j1Pathfinding.h"
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

	collider = App->collision->AddCollider({ (int)position.x,(int)position.y,BOO_WIDTH,BOO_HEIGHT }, COLLIDER_BOO, this);
	return ret;
}

bool Enemy_Boo::Start()
{
	

	//load texture
	text_boo = App->tex->Load("textures/mario.png");

	is_path_done = true;
	path = 0;
	last_path = 0;
	path_size = 0;
	path_stopped = false;
	pathfinding = false;
	find_path = true;
	create_path = true;

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

	if ((position.x - App->entity_manager->player->position.x <= 0 && App->entity_manager->player->entity_state == IDLE) ||
		(position.x - App->entity_manager->player->position.x >= 0 && App->entity_manager->player->entity_state == IDLE))
		boo_chase = true;
	else
		boo_chase = false;

	if (boo_chase)
	{
		Move();

		if (pathfinding)
		{
			// go to
			if (!Find_a_Path() && find_path)
			{
				find_path = false;
			}
			else
			{
				//in case the enemy reaches the final of the path
				pathfinding = false;
				is_path_done = true;
			}

		}
	}


	if(collider != NULL)
	collider->SetPos(position.x, position.y);

	pathfind_timer += dt;
	return ret;
}

bool Enemy_Boo::PostUpdate()
{
	Draw();
	App->render->Blit(text_boo, position.x, position.y, &current->GetCurrentFrame());
	/*BROFILER_CATEGORY("BooPostUpdate", Profiler::Color::Gainsboro);
	bool ret = true;

	
	//Blit player
	

	boo_quadrant_1.x = position.x / TILE_WIDTH;
	boo_quadrant_2.x = (position.x + BOO_WIDTH) / TILE_WIDTH;

	boo_quadrant_1.y = position.y / TILE_WIDTH;
	boo_quadrant_2.y = (position.y + BOO_HEIGHT) / TILE_WIDTH;
	*/
	return true;
}

bool Enemy_Boo::CleanUp()
{
	bool ret = true;

	collider->to_delete = true;
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
	Pathfinding();

	
}

void Enemy_Boo::Pathfinding()
{
	BROFILER_CATEGORY("Boo Pathfinding", Profiler::Color::Orange)

		if (is_path_done)
		{
			is_path_done = false;
			path = 0;
			last_path = 0;
			path_size = 0;
			path_stopped = false;
			pathfinding = false;
			find_path = true;
			last_path = path;
			create_path = true;
		}

	//create a path
	if (pathfind_timer >= 0.2f)
	{
		if (create_path)
		{
			fPoint destination;
			destination.x = App->entity_manager->player->position.x;
			destination.y = App->entity_manager->player->position.y;

			//if the path creates->
			if (CreatePath(destination))
			{
				pathfinding = true;
				create_path = false;
			}
		}
		pathfind_timer = 0;
	}
}

bool Enemy_Boo::CreatePath(fPoint destination)
{
	BROFILER_CATEGORY("Boo CreatePath", Profiler::Color::Orange)

		bool ret = false;

	//we call the pathfinding module and create a path, the bool we send is to know if the enmy can go in diagonal lines
	if (App->path_finding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(destination.x, destination.y),true) > -1)
	{
		//we save the last path in a variable
		last_pathfinding = App->path_finding->GetLastPath();
		path_size = last_pathfinding->Count();
		path = 1;

		//we clear the variable before pushing back our points
		mlast_pathfinding.Clear();

		for (int i = 0; i < path_size; ++i)
		{
			mlast_pathfinding.PushBack(*last_pathfinding->At(i));
			ret = true;
		}
	}

	return ret;
}
bool Enemy_Boo::Find_a_Path()
{
	BROFILER_CATEGORY("BooFindPath", Profiler::Color::Orange)

		bool ret = true;

	//when boo needs more than one step to reach player, if he doesn't then player probably dead af
	if (path_size > 1)
	{
		iPoint go_to = App->map->MapToWorld(mlast_pathfinding[path].x, mlast_pathfinding[path].y);
		//once we know where boo gotta go we send it to the function that moves him
		Movement(go_to);

		if (GetPositionINT() == go_to)
		{
			if (path < path_size - 1)
				path++;
		}

		if (GetPositionINT() == App->map->MapToWorld(mlast_pathfinding[path_size - 1].x, mlast_pathfinding[path_size - 1].y))
			ret = false;
	}
	else
		ret = false;

	return ret;
}

void Enemy_Boo::Movement(iPoint go_to)
{
	if (position.x < go_to.x)
		position.x += 5.0f, entity_state = MOVE_LEFT;
	else if (position.x > go_to.x)
		position.x -= 5.0f, entity_state = MOVE_RIGHT;
	if (position.y < go_to.y)
		position.y += 5.0f;
	else if (position.y > go_to.y)
		position.y -= 5.0f;
}

iPoint Enemy_Boo::GetPositionINT() const
{
	return iPoint(position.x, position.y);
}