#include "j1Label.h"
#include "j1Fonts.h"
#include "j1Render.h"

j1Label::j1Label() : j1Object()
{
	//font = fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
}

j1Label::j1Label(iPoint pos, char* label_text) : j1Object()
{
	this->type = LABEL;
	this->position = pos;
	this->label_text = label_text;

	font = App->fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
	text = App->fonts->Print(this->label_text, { 255,255,255,255 }, font);
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

	App->render->Blit(text, this->position.x, this->position.y);
}