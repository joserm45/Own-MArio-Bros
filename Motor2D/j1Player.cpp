#include "j1Player.h"
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

j1Player::j1Player() : j1Module()
{
	name.create("player");

}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node&)
{
	bool ret = true;
	position.x = 0;
	position.y = 0;
	return ret;
}

bool j1Player::Start()
{
	bool ret = true;
	//load texture
	//graph = App->tex->Load();

	//load collider

	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	//movement

	//right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		position.x += PLAYER_SPEED;
	}
	//left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		position.x -= PLAYER_SPEED;
	}
	//jump
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		position.y += PLAYER_JUMP;
	}
	//down
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		position.y -= PLAYER_SPEED/2;
	}

	return ret;
}

bool j1Player::PostUpdate()
{
	bool ret = true;
	
	//Blit
	//App->render->Blit(graph, position.x, position.y, ? animation.h ? );

	return ret;
}

bool j1Player::CleanUp() 
{
	bool ret = true;

	return ret;
}

bool j1Player::Save(pugi::xml_node&) const
{
	bool ret = true;

	return ret;
}

bool j1Player::Load(pugi::xml_node&)
{
	bool ret = true;

	return ret;
}

void j1Player::Draw()
{
	//Load Animations
}