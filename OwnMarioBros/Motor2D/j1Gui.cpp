#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Object.h"
#include "j1Fonts.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");


	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	fPoint pos = { 300.0f,350.0f };
	SDL_Rect rect = { 0,113,229,69 };
	CreateObject(IMAGE, pos, rect);
	pos = { 100.0f,25.0f };
	rect = { 100,100,100,100 };
	CreateObject(LABEL, pos, rect);
	return true;
}

bool j1Gui::Update(float dt)
{

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

void j1Gui::CreateObject(TYPE_OBJECT ob, fPoint pos, SDL_Rect rect)
{
	if (ob == LABEL)
	{
		Object* label = new Object();
		label->position = pos;
		label->label_text = "Hello World";

		if (label != nullptr)
			objects.add(label);

	}
	else if (ob == IMAGE)
	{
		Object* image = new Object();
		image->atlas_pos = rect;
		image->position = pos;

		objects.add(image);
	}

}

void j1Gui::DeleteObject(Object ob)
{

}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

