#include "j1Label.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "p2SString.h"
#include "j1FadeToBlack.h"

j1Label::j1Label() : j1Object()
{
	//font = fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
}

j1Label::j1Label(iPoint pos, uint* num_text) : j1Object()
{
	this->type = NUMBER;
	this->position = pos;
	this->number_text = num_text;

	font = App->fonts->Load("fonts/open_sans/MarioFont.ttf", 10);
	//text = App->fonts->Print("null", { 255,255,255,255 }, font);
	text = App->tex->textures.add(App->fonts->Print("null", { 255,255,255,255 }, font))->data;
}

j1Label::j1Label(iPoint pos, char* label_text) : j1Object()
{

	this->type = LABEL;
	this->position = pos;
	this->label_text = label_text;

	font = App->fonts->Load("fonts/open_sans/MarioFont.ttf", 10);
	//text = App->fonts->Print(this->label_text, { 255,255,255,255 }, font);
	text = App->tex->textures.add(App->fonts->Print(this->label_text, { 255,255,255,255 }, font))->data;
}

void j1Label::Start()
{
	//font = App->fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
}

j1Label::~j1Label()
{

};

void j1Label::Draw()
{

	if (type == NUMBER)
	{
		//if (App->fade_to_black->current_step != j1FadeToBlack::fade_to_black) // TODO: Crash when dies 2 times
		//{
			p2SString string;
			if(number_text != nullptr)
			sprintf_s(string.str, sizeof(string), "%i", *number_text);

			App->tex->UnLoad(text);
			text = App->tex->textures.add(App->fonts->Print(string.str, { 255,255,255,255 }, font))->data;
		//}

	}

		App->render->Blit(text, (this->position.x - App->render->camera.x), this->position.y);

}