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
#include "j1Scene.h"
#include "j1Slider.h"
#include "j1Button.h"


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
	CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu*/

	//buttons intro menu 
	CreateObject(BUTTON, { 582,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 },PLAY); //button start 
	CreateObject(LABEL, { 605,50 }, {NULL,NULL,NULL,NULL},{ NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start
	CreateObject(BUTTON, { 582,68 }, { 441,543,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CONTINUEOFF); //button unclickable continue 
	CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CONTINUE");//text continue
	CreateObject(BUTTON, { 582,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
	CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SETTINGS");//text settings
	CreateObject(BUTTON, { 582,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
	CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
	CreateObject(BUTTON, { 582,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 },EXIT); //button exit 
	CreateObject(LABEL, { 611,146}, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "EXIT");//text exit*

	//trying slider
	//CreateObject(SLIDER, { 280,50 }, { 533,480,135,10 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "HORIZONTAL");
	
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
	if (debug_UI == true)
	{
		for (int i = 0; i < objects.count(); i++)
		{
			DrawDebugUI(objects[i]);
		}
	}

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
			if (OnHover({ item->data->position.x,item->data->position.y,item->data->atlas_pos.w,item->data->atlas_pos.h }) && App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				item->data->mouse_hover = true;
				item->data->clicked = true;
				if (item->data->button_type != CONTINUEOFF)
				{
					item->data->active = true;
				}
				item->data->Draw();
				item->data->OnClick(item->data);
			}
			else if (OnHover({ item->data->position.x,item->data->position.y,item->data->atlas_pos.w,item->data->atlas_pos.h }))
			{
				item->data->mouse_hover = true;
				if (item->data->button_type != CONTINUEOFF)
				{
					item->data->active = true;
				}
				item->data->Draw();
			}
			else
			{
				item->data->mouse_hover = false;
				item->data->clicked = false;
				item->data->Draw();
			}
		
		}
		else if (item->data->type == SLIDER)
		{
			item->data->Draw();
			if (OnHover({ item->data->position.x,item->data->position.y,item->data->atlas_pos.w,item->data->atlas_pos.h }) && App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				item->data->OnDrag(item->data);
			}
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
	/*p2List_item<j1Object*>* item = objects.start;
	while (item != nullptr)
	{
		SDL_DestroyTexture(item->data->atlas_pos);
		item = item->next;
	}*/
	objects.clear();

	return true;
}

void j1Gui::CreateObject(TYPE_OBJECT obj_type, iPoint pos, SDL_Rect rect, SDL_Rect press, SDL_Rect hover, BUTTON_TYPE btn_type, char* label_text)
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
	else if (obj_type == BUTTON)
	{
		j1Button* button = new j1Button(pos,rect,press,hover,btn_type);

		objects.add(button);
	}
	else if (obj_type == SLIDER)
	{
		j1Slider* slider = new j1Slider(pos, rect, label_text);

		objects.add(slider);
	}

}

void j1Gui::DeleteObject(j1Object* obj)
{
	if (obj != nullptr)
	{
		p2List_item<j1Object*>* item = objects.start;

		while (item != NULL)
		{
			if (item->data == obj)
			{

				if (obj != NULL)
				{
					RELEASE(obj);
					objects.del(item);
				}

				return;
			}

			item = item->next;
		}
	}
}

bool j1Gui::OnHover(SDL_Rect rect)
{
	int x, y = 0;
	App->input->GetMousePosition(x, y);

	if (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h))
	{		
		return true;
	}
	return false;
}


const bool j1Gui::Trigger(j1Object* obj)
{
	j1Button* button = (j1Button*)obj;

	switch (button->button_type)
	{
	case PLAY:
	{
		CleanUp();
		App->scene->scene_starts = true;
		App->scene->Start();
		CreateObject(LABEL, { 40,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SCORE");
		CreateObject(LABEL, { 40,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "0");
		CreateObject(LABEL, { 340,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "LIVES");
		CreateObject(LABEL, { 340,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "3");
		CreateObject(LABEL, { 640,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "COINS");
		CreateObject(IMAGE, { 694,18 }, { 565,490,10,14 }); //image coin
		CreateObject(LABEL, { 640,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "0");
		CreateObject(LABEL, { 940,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "TIME");
		CreateObject(LABEL, { 940,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "0");
		break;
	}
	case CONTINUEON:
	{

		break;
	}
	case SETTINGS:
	{
		CleanUp();
		CreateObject(IMAGE, { 0,0 }, { 0, 240, 1024, 240 }); //background settings menu
		CreateObject(IMAGE, { 575,40 }, { 441, 564, 92, 21 }); //box image behind music
		CreateObject(LABEL, { 596,46 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "MUSIC"); //music text
		CreateObject(SLIDER, { 575,80 }, { 533,480,135,10 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "HORIZONTAL");//music slider back
		CreateObject(IMAGE, { 575,120 }, { 441, 564, 92, 21 }); //box image behind fx volume
		CreateObject(LABEL, { 577,126 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "fx volume"); //fx volume text
		CreateObject(SLIDER, { 575,160 }, { 533,480,135,10 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "HORIZONTAL");//fx volum slider back
		CreateObject(BUTTON, { 900,200 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, BACK); //button back 
		CreateObject(LABEL, { 926,206 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "BACK"); //text back
		break;
	}
	case CREDITS:
	{
		CleanUp();
		CreateObject(IMAGE, { 0,0 }, { 0, 240, 1024, 240 }); //background settings menu

		CreateObject(BUTTON, { 900,200 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, BACK); //button back 
		CreateObject(LABEL, { 926,206 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "BACK"); //text back
		break;
	}
	case EXIT:
	{
		exit(0);
		break;
	}
	case BACK:
	{
		CleanUp();
		CreateObject(IMAGE, { 0,0 }, { 0, 0, 1024, 240 }); //background image intro menu
		CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
		CreateObject(IMAGE, { 570,27 }, { 325,480,116,150 }); //box image below buttons intro menu
		CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
		CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu*/

		//buttons intro menu 
		CreateObject(BUTTON, { 582,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, PLAY); //button start 
		CreateObject(LABEL, { 605,50 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start
		CreateObject(BUTTON, { 582,68 }, { 441,543,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CONTINUEOFF); //button unclickable continue 
		CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CONTINUE");//text continue
		CreateObject(BUTTON, { 582,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
		CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SETTINGS");//text settings
		CreateObject(BUTTON, { 582,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
		CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
		CreateObject(BUTTON, { 582,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, EXIT); //button exit 
		CreateObject(LABEL, { 611,146 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "EXIT");//text exit*
		break;
	}
	case SAVEANDRESUME:
	{

		break;
	}
	case SAVEANDEXIT:
	{

		break;
	}

	default:
		break;
	}
	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

void j1Gui::DrawDebugUI(j1Object* obj) const
{
	SDL_Rect quad = { obj->position.x, obj->position.y , obj->atlas_pos.w , obj->atlas_pos.h };
	App->render->DrawQuad(quad, 255, 255, 255, 255, false);
}
// class Gui ---------------------------------------------------

