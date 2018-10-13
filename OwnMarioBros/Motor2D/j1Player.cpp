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
#include "j1Collision.h"

j1Player::j1Player() : j1Module()
{
	name.create("player");

	Load_Animation();
	
}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& node)
{
	bool ret = true;
	if (node != NULL)
	{
		position.x = node.child("player").child("position").attribute("x").as_int();
		position.y = node.child("player").child("position").attribute("y").as_int();;
	}
	else
	{
		position.x = 86;
		position.y = 174;
	}
	
	//current = &right_idle;
	status = IDLE;
	return ret;
}

bool j1Player::Start()
{
	
	//load texture
	text_player = App->tex->Load("textures/mario.png");
	collider_player = App->collision->AddCollider({ position.x,position.y,MARIO_WITH,MARIO_HEIGHT }, COLLIDER_PLAYER, this);
	//load collider

	return true;
}

bool j1Player::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	//Movement
	moving = false;
	position.y += GRAVITY;



	//right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		position.x += PLAYER_SPEED;
		status = RIGHT;
		moving = true;
		back = false;
	}
	//left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		position.x -= PLAYER_SPEED;
		status = LEFT;
		moving = true;
		back = true;
	}
	//jump
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		position.y -= PLAYER_JUMP;
		status = JUMP;
		moving = true;
	}
	//duck
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		//position.y -= PLAYER_SPEED;
		status = DUCK;
		moving = true;
	}

	//die
	//to check if animation works for the moment
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		status = DIE;
		position.y -= 100;
		moving = false;
		App->audio->PlayMusic("audio/music/life_lost.ogg", 0.3);
	}

	//god mode
	if (App->scene->god_mode == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			position.y -= PLAYER_SPEED;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			position.y += PLAYER_SPEED;
		}

	}

	//status check
	if (moving == false && status != DIE)
	{
		status = IDLE;
	}

	CameraMovement();

	collider_player->SetPos(position.x, position.y);

	return ret;
}

bool j1Player::PostUpdate()
{
	bool ret = true;

	Draw();
	//Blit player
	App->render->Blit(text_player, position.x, position.y, &current->GetCurrentFrame());


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
	//save 
	return ret;
}

bool j1Player::Load(pugi::xml_node&)
{
	bool ret = true;
	//load
	return ret;
}

void j1Player::CameraMovement()
{
	int relative_pos_player = position.x + App->render->camera.x;

	if (relative_pos_player < App->render->border)
	{
		App->render->camera.x = -(position.x - App->render->border);
	}
	if (relative_pos_player > App->render->camera.w - App->render->border)
	{
		App->render->camera.x = -(position.x - (App->render->camera.w - App->render->border));
	}
	if (App->render->camera.x > 0)
	{
		App->render->camera.x = 0;
	}
	if (App->render->camera.x < -2555)
	{
		App->render->camera.x = -2555;
	}
}

void j1Player::Draw()
{
	//Draw Animations
	switch (status)
	{
		case IDLE:
		{
			if (App->scene->god_mode == false) 
			{
				if (back == false)
				{
					current = &right_idle;
					break;
				}
				else if (back == true)
				{
					current = &left_idle;
					break;
				}
			}
			else if (App->scene->god_mode == true)
			{
				if (back == false)
				{
					current = &god_right_idle;
					break;
				}
				else if (back == true)
				{
					current = &god_left_idle;
					break;
				}
			}
		}
		case LEFT:
		{
			if (App->scene->god_mode == false)
			{
				current = &move_left;
				break;
			}
			else if (App->scene->god_mode == true)
			{
				current = &god_move_left;
				break;
			}
		}
		case RIGHT:
		{
			if (App->scene->god_mode == false)
			{
				current = &move_right;
				break;
			}
			else if (App->scene->god_mode == true)
			{
				current = &god_move_right;
				break;
			}
		}
		case JUMP:
		{
			if (App->scene->god_mode == false)
			{
				if (back == false)
				{
					current = &right_jump;
					break;
				}
				else if (back == true)
				{
					current = &left_jump;
					break;
				}
			}
			else if (App->scene->god_mode == true)
			{
				if (back == false)
				{
					current = &god_right_jump;
					break;
				}
				else if (back == true)
				{
					current = &god_left_jump;
					break;
				}
			}
		}
		case DUCK:
		{
			if (App->scene->god_mode == false)
			{
				if (back == false)
				{
					current = &right_duck;
					break;
				}
				else if (back == true)
				{
					current = &left_duck;
					break;
				}
			}
			else if (App->scene->god_mode == true)
			{
				if (back == false)
				{
					current = &god_right_duck;
					break;
				}
				else if (back == true)
				{
					current = &god_left_duck;
					break;
				}
			}
		}
		case DIE:
		{
			current = &die;
		}
	}

}

void j1Player::Load_Animation()
{
	//MARIO

	//idle
	right_idle.PushBack({ 258,1,16,32 });
	left_idle.PushBack({ 239,1,16,32 });

	//Walk right
	move_right.PushBack({ 296,3,16,30 });
	move_right.PushBack({ 315,2,14,31 });
	move_right.PushBack({ 331,1,16,32 });
	move_right.speed = ANIMATION_SPEED;

	//Walk left
	move_left.PushBack({ 201,3,16,30 });
	move_left.PushBack({ 184,2,14,31 });
	move_left.PushBack({ 166,1,16,32 });
	move_left.speed = ANIMATION_SPEED;

	//Jump 
	//right_jump.PushBack({ 350,1,16,32 });
	right_jump.PushBack({ 369,1,16,32 });
	//right_jump.PushBack({ 388,1,16,32 });
	//right_jump.speed = ANIMATION_SPEED;
	//right_jump.loop = 0;

	//left_jump.PushBack({ 147,1,16,32 });
	left_jump.PushBack({ 128,1,16,32 });
	//left_jump.PushBack({ 111,1,16,32 });
	//left_jump.speed = ANIMATION_SPEED;
	//left_jump.loop = 0;

	//duck
	right_duck.PushBack({ 277, 1, 16, 32 });
	left_duck.PushBack({ 220, 1, 16, 32 });

	//die 
	die.PushBack({ 516, 1, 24, 34 });
	die.PushBack({ 540, 1, 24, 34 });
	die.PushBack({ 564, 1, 24, 34 });
	die.PushBack({ 588, 1, 24, 34 });
	die.PushBack({ 612, 1, 24, 34 });
	die.PushBack({ 636, 1, 24, 34 });
	die.PushBack({ 660, 1, 24, 34 });
	die.speed = ANIMATION_SPEED;


	//GOD MODE MARIO

	//idle
	god_right_idle.PushBack({ 258,129,16,32 });
	god_left_idle.PushBack({ 239,129,16,32 });

	//Walk right
	god_move_right.PushBack({ 296,131,16,30 });
	god_move_right.PushBack({ 315,130,14,31 });
	god_move_right.PushBack({ 331,129,16,32 });
	god_move_right.speed = ANIMATION_SPEED;

	//Walk left
	god_move_left.PushBack({ 201,131,16,30 });
	god_move_left.PushBack({ 184,130,14,31 });
	god_move_left.PushBack({ 166,129,16,32 });
	god_move_left.speed = ANIMATION_SPEED;

	//Jump 
	//god_right_jump.PushBack({ 350,129,16,32 });
	god_right_jump.PushBack({ 369,129,16,32 });
	//god_right_jump.PushBack({ 388,129,16,32 });
	//god_right_jump.speed = ANIMATION_SPEED;
	//god_right_jump.loop = 0;

	//god_left_jump.PushBack({ 147,129,16,32 });
	god_left_jump.PushBack({ 128,129,16,32 });
	//god_left_jump.PushBack({ 111,129,16,32 });
	//god_left_jump.speed = ANIMATION_SPEED;
	//god_left_jump.loop = 0;

	//duck
	god_right_duck.PushBack({ 277, 129, 16, 32 });
	god_left_duck.PushBack({ 220, 129, 16, 32 });
	



	/*
	//LITTLE MARIO
	right_idle = { 277,44,12,16 };

	move_right.PushBack({ 54,181,27,32 });
	move_right.PushBack({ 93,181,27,32 });
	move_right.PushBack({ 11,220,27,32 });
	move_right.PushBack({ 54,218,27,32 });
	move_right.PushBack({ 91,219,27,32 });
	
	jump = { 126,220,34,32 };
	
	//die = { 127,263,32,28 };
	*/


}