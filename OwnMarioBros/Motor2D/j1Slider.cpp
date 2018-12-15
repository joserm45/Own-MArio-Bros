#include "j1Slider.h"
#include "j1Render.h"

j1Slider::j1Slider() {}

j1Slider::j1Slider(iPoint pos, SDL_Rect rect, char* label_text)
{
	this->type = SLIDER;
	this->position = pos;
	this->atlas_pos = rect;
	
	if (strcmp(label_text, "VERTICAL") == 0)
	{
		type_slider = VERTICAL;
		min = position.y + 1;
		max = position.y + rect.h - 9;
	}
	else if (strcmp(label_text, "HORIZONTAL") == 0)
	{
		type_slider = HORIZONTAL;
		min = position.x + 1;
		max = position.x + rect.w - 9;
	}
	
}
j1Slider::~j1Slider()
{

}

void j1Slider::Draw()
{
	App->render->Blit(App->gui->atlas, this->position.x, this->position.y, &atlas_pos);
}

void j1Slider::OnDrag(j1Object * obj)
{
	int x, y;
	App->input->GetMousePosition(x, y);

	if (mouse_hover == true && active == true)
	{
		if (y > prev_mouse.y)
		{
			if (position.y < max)
				position.y += y - prev_mouse.y;
		}
		else if (y < prev_mouse.y)
		{
			if (position.y > min)
				position.y -= prev_mouse.y - y;
		}
	}
}