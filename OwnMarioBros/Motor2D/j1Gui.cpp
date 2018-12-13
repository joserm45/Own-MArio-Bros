#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Object.h"
#include "j1Image.h"
#include "j1Fonts.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{
	App->tex->UnLoad(atlas);
}

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

	SDL_Rect rect = { 0,0,1024,240 };

	CreateObject(IMAGE, {1110,0}, rect);

	CreateObject(IMAGE, { 500,200 }, { 0,480, 325,162 });

	CreateObject(IMAGE, { 0,0 }, { 325,480,116,150 });

	CreateObject(LABEL, { 0,0 }, {NULL,NULL,NULL,NULL}, "Hello World");
	return true;
}

bool j1Gui::PreUpdate()
{
	return true;
}

// Update all guis
bool j1Gui::Update(float dt)
{
	p2List_item<j1Object*>* item = objects.start;
	while (item != nullptr)
	{
		if (item->data->type == IMAGE)
		{
			item->data->Draw();
		}
		else if (item->data->type == LABEL)
		{
			item->data->Draw();
		}
		item = item->next;
	}
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

void j1Gui::CreateObject(TYPE_OBJECT obj_type, iPoint pos, SDL_Rect rect, char* label_text)
{
	if (obj_type == LABEL)
	{
		j1Label* label = new j1Label(pos,label_text);

		objects.add(label);

	}
	else if (obj_type == IMAGE)
	{
		j1Image* image = new j1Image(pos,rect);

		objects.add(image);
	}

}

void j1Gui::DeleteObject(j1Object* obj)
{

}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

