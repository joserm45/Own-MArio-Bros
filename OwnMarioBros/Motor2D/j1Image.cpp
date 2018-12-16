#include "j1Image.h"
#include "j1Render.h"

#include "Brofiler\Brofiler.h"

j1Image::j1Image() {}

j1Image::j1Image(iPoint pos, SDL_Rect rect)
{
	BROFILER_CATEGORY("ImageContructor", Profiler::Color::Thistle);
	this->type = IMAGE;
	this->position = pos;
	this->atlas_pos = rect;
}
j1Image::~j1Image()
{

}

void j1Image::Draw()
{
	BROFILER_CATEGORY("ImageDraw", Profiler::Color::Aquamarine);
	App->render->Blit(App->gui->atlas, (this->position.x - App->render->camera.x), this->position.y, &atlas_pos);
}
