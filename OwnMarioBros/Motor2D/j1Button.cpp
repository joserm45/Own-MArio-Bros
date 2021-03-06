#include "j1Button.h"
#include "j1Audio.h"
#include "j1Scene.h"

#include "Brofiler\Brofiler.h"

j1Button::j1Button()
{
}

j1Button::j1Button(iPoint pos, SDL_Rect rect, SDL_Rect pressed, SDL_Rect hover, BUTTON_TYPE btn_type)
{
	BROFILER_CATEGORY("ButtonContructor", Profiler::Color::FireBrick);
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
	BROFILER_CATEGORY("ButtonDraw", Profiler::Color::Khaki);
	App->render->Blit(App->gui->GetAtlas(),(position.x - App->render->camera.x), position.y, &atlas_pos);
	if (mouse_hover == true && clicked == true && active == true)
	{
		App->render->Blit(App->gui->GetAtlas(), (position.x - App->render->camera.x), position.y, &pressed);
	}
	else if (mouse_hover == true && active == true)
	{
		App->render->Blit(App->gui->GetAtlas(), (position.x - App->render->camera.x), position.y, &hover);
	}
}

void j1Button::OnClick(j1Object * obj)
{
	BROFILER_CATEGORY("ButtonOnClick", Profiler::Color::Salmon);
	if (mouse_hover == true && active == true && clicked == true)
	{
		App->audio->PlayFx(App->scene->click_sound);
		App->gui->Trigger(obj);
		//App->audio->PlayFx(); TODO
		
	}
}

const bool j1Button::Trigger(j1Object * obj)
{
	return false;
}
