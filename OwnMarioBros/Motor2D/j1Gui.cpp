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

	//intro menu background
	CreateObject(IMAGE, {0,0}, rect); //background image intro menu
	CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
	CreateObject(IMAGE, { 570,27 }, { 325,480,116,150 }); //box image below buttons intro menu
	CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
	CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu

	//buttons intro menu 
	//CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(IMAGE, { 582,44 }, { 441,480,92,21 }); //button start CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(LABEL, { 605,50 }, {NULL,NULL,NULL,NULL}, "START"); //text start
	CreateObject(IMAGE, { 582,68 }, { 441,543,92,21 }); //button unclickable continue CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, "CONTINUE");//text continue
	CreateObject(IMAGE, { 582,92 }, { 441,480,92,21 }); //button settings CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, "SETTINGS");//text settings
	CreateObject(IMAGE, { 582,116 }, { 441,480,92,21 }); //button credits CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, "CREDITS");//text credits
	CreateObject(IMAGE, { 582,140 }, { 441,480,92,21 }); //button exit CHANGE IMAGE TO BUTTON WHEN BUTTON IS DONE!!!!!!!
	CreateObject(LABEL, { 611,146}, { NULL,NULL,NULL,NULL }, "EXIT");//text exit


	/*
	Intro Menu Background ({0,0,1024,240 });
	Super Mario Bros Box con Texto ({ 0,480, 325,162 });
	Box donde se ponen los botones ({ 325,480,116,150 });
	Boton Normal ({ 441,480,92,21 });
	Boton Hover ({ 441,501,92,21 });
	Boton On Click ({ 441,522,92,21 });
	Boton Unclickable (para el continue) ({ 441,543,92,21 });
	Box Fondo para texto solo (como el boton pero para poner por ejemplo "Volume" y abajo el slider) ({ 441,564,92,21 });
	Settings/Credits Menu Background ({ 0,240,1024,240 });
	Slider Fondo ({ 533,460,135,10 });
	Pon estos una posicion mas abajo del slider fondo para que el circulito ese este en medio:
	Slider Circulo Normal ({ 668,480,8,8 });
	Slider Circulo on Click ({ 676,480,8,8 });

	Mario ({ 533,490,16,32 });
	Goomba ({ 549,490,16,16 });
	Coin In game UI ({ 565,490,10,14 });
	*/

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
		else if (item->data->type == BUTTON)
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

