#include "j1Button.h"

j1Button::j1Button()
{
}

j1Button::j1Button(iPoint pos, SDL_Rect rect, SDL_Rect pressed, SDL_Rect hover, BUTTON_TYPE btn_type)
{
	type = BUTTON;

	this->position = pos;
	this->atlas_pos = rect;
	this->pressed = pressed;
	this->hover = hover;
	this->button_type = btn_type;
}

j1Button::~j1Button()
{
}

void j1Button::Draw()
{

	if (mouse_hover == true && clicked == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &pressed);
	}
	else if (mouse_hover == true)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &hover);
	}
	else if (mouse_hover == false)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &atlas_pos);
	}
}

void j1Button::OnClick(j1Object * obj)
{
	if (mouse_hover == true && active == true && clicked == true)
	{
		App->gui->Trigger(obj);
		//App->audio->PlayFx(); TODO

	}
}

const bool j1Button::Trigger(j1Object * obj)
{
	return false;
}
