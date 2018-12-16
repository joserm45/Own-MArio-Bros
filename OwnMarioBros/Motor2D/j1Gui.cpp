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
#include "j1Audio.h"
#include "j1Map.h"

#include "Brofiler\Brofiler.h"

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
	BROFILER_CATEGORY("GUIAwake", Profiler::Color::Moccasin);
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	App->audio->PlayMusic("audio/music/intro.ogg");
	App->audio->VolumeStart(App->audio->volume);
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	BROFILER_CATEGORY("GUIStart", Profiler::Color::SeaGreen);
	App->scene->scene_menu = true;
	if (save_exit_menu)
	{
		App->tex->UnLoad(atlas);
		App->map->UnloadMap();
		App->entity_manager->DestroyEntities();
		save_exit_menu = false;
	}

	atlas = App->tex->Load(atlas_file_name.GetString());

	//SDL_Rect rect = { 0,0,1024,240 };

	//intro menu background
	CreateObject(IMAGE, { 0,0 }, { 0, 0, 1024, 240 }); //background image intro menu
	CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
	CreateObject(IMAGE, { 570,27 }, { 325,480,116,150 }); //box image below buttons intro menu
	CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
	CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu*/

	//buttons intro menu 
	CreateObject(BUTTON, { 582,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 },PLAY); //button start 
	CreateObject(LABEL, { 605,50 }, {NULL,NULL,NULL,NULL},{ NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start
	CreateObject(BUTTON, { 582,68 }, { 441,543,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CONTINUE); //button unclickable continue 
	CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CONTINUE");//text continue
	CreateObject(BUTTON, { 582,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
	CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SETTINGS");//text settings
	CreateObject(BUTTON, { 582,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
	CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
	CreateObject(BUTTON, { 582,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 },EXIT); //button exit 
	CreateObject(LABEL, { 611,146}, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "EXIT");//text exit*
	CreateObject(BUTTON, { 582,182 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, WEBSITE); //button web 
	CreateObject(LABEL, { 594,188 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "WEBSITE");//text web

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
	BROFILER_CATEGORY("GUIUpdate", Profiler::Color::DarkGreen);
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("save_game.xml");;

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
			if (OnHover({ item->data->position.x,item->data->position.y,item->data->atlas_pos.w,item->data->atlas_pos.h }) && App->input->GetMouseButtonDown(1) == KEY_DOWN)// mouse down print
			{
				item->data->mouse_hover = true;
				item->data->clicked = true;
				if (item->data->button_type != CONTINUE)
				{
					item->data->active = true;
					item->data->Draw();
					item->data->OnClick(item->data);
				}
				else if (item->data->button_type == CONTINUE && result)
				{
					item->data->active = true;
					item->data->Draw();
					item->data->OnClick(item->data);
				}

			}
			else if (OnHover({ item->data->position.x,item->data->position.y,item->data->atlas_pos.w,item->data->atlas_pos.h })) // hover print
			{
				item->data->mouse_hover = true;
				if (item->data->button_type != CONTINUE)
				{
					item->data->active = true;
					item->data->Draw();
				}
				else if (item->data->button_type == CONTINUE && result == true)
				{

					item->data->active = true;
					item->data->Draw();
				}
			}
			else if (item->data->button_type != CONTINUE || item->data->button_type == CONTINUE && result == true)
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
		/*else if (item->data->type == NUMBER && result == true)
		{
			item->data->Draw();
		}*/
		
		/*if (debug_UI == true)
		{
			SDL_Rect quad;
			if (item->data->type != LABEL && item->data->type == NUMBER)
			{
				quad = { item->data->position.x - App->render->camera.x, item->data->position.y, item->data->atlas_pos.w,item->data->atlas_pos.h };
			}
			else if (item->data->type == LABEL || item->data->type == NUMBER)
			{
				App->fonts->CalcSize(item->data->label_text, width_font, height_font, item->data->font);
				if(item->data->type == NUMBER)
					quad = { item->data->position.x - App->render->camera.x, item->data->position.y, width_font , height_font };
				else
					quad = { item->data->position.x - App->render->camera.x, item->data->position.y, width_font , height_font };
			}
			App->render->DrawQuad(quad, 255, 255, 0, 255, false);
		}*/

		if (debug_UI == true)
		{
			SDL_Rect quad;
			if (item->data->type != LABEL)
			{
				quad = { item->data->position.x - App->render->camera.x, item->data->position.y, item->data->atlas_pos.w,item->data->atlas_pos.h };

			}
			else if (item->data->type == LABEL)
			{
				App->fonts->CalcSize(item->data->label_text, width_font, height_font, item->data->font);
				quad = { item->data->position.x - App->render->camera.x, item->data->position.y, width_font , height_font };
			}
			else if (item->data->type == NUMBER)
			{
				//App->fonts->CalcSize((char*)item->data->number_text, width_font, height_font, item->data->font);
				quad = { item->data->position.x - App->render->camera.x, item->data->position.y, width_font , height_font };
			}
			App->render->DrawQuad(quad, 255, 255, 0, 255, false);
		}

		item = item->next;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	BROFILER_CATEGORY("GUIPostUdate", Profiler::Color::NavajoWhite);
	//TODO
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && App->scene->in_game == true)
	{
		App->audio->PlayFx(App->scene->pause_sound);
		//App->scene->paused = false
		App->scene->in_game = false;
		game_paused = true;
		//App->scene->scene_menu == true;
		SDL_SetTextureAlphaMod(App->gui->atlas, 170);
		//CreateObject(IMAGE, { App->render->camera.x,App->render->camera.y }, { 0,0,1024,240 });
		//ret = false;
		/*CreateObject(IMAGE, { 0,0 }, { 0, 0, 1024, 240 }); //background image intro menu
		CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
		CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
		CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu*/

		CreateObject(IMAGE, { 0,0 }, { 0, 642, 1024, 240 }); //background pause menu
		//CreateObject(IMAGE, { 570 ,27 }, { 325,480,116,150 }); //box image below buttons intro menu
		//CreateObject(BUTTON, {582 ,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, PLAY); //button start 
		//CreateObject(LABEL, {  605 ,50 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start

		CreateObject(BUTTON, { 466 ,68 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, RESUME); //button unclickable continue 
		CreateObject(LABEL, { 482 ,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "RESUME");//text continue

		CreateObject(IMAGE, { 466, 92 }, { 441, 564, 92, 21 }); //background box for volume
		//CreateObject(BUTTON, { 466 ,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
		CreateObject(LABEL, { 482 ,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "VOLUME");//text volume
		CreateObject(BUTTON, { 465,115 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLMINUS); //button volume MINUS
		CreateObject(LABEL, { 470,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "-");
		CreateObject(BUTTON, { 537,115 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLPLUS); //button volume PLUS
		CreateObject(LABEL, { 543,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "+");

		//CreateObject(BUTTON, { 466 ,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
		//CreateObject(LABEL, { 478 ,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
		CreateObject(BUTTON, { 466 ,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SAVEANDEXIT); //button main menu 
		CreateObject(LABEL, { 468 ,146 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "MAIN MENU");//text main menu
	}

	else if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && game_paused == true)
	{
		game_paused = false;
		App->scene->in_game = true;
		p2List_item<j1Object*>* item = objects.end;
		while (item->data->position.y != 32)
		{
			objects.del(item);
			item = item->prev;
		}
	}

	if (game_over == true)
	{
		game_paused = false;
		App->scene->in_game = false;
		App->scene->scene_menu = true;
		save_exit_menu = true;
		//App->entity_manager->active = false;
		App->audio->StopMusic();
		App->audio->PlayMusic("audio/music/intro.ogg");
		CleanUp();
		game_over = false;
	}

	if (load_finish == true)
	{
		CreateObject(LABEL, { 40,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SCORE");
		CreateObject(NUMBER, { 40,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->score);
		CreateObject(LABEL, { 340,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "LIVES");
		CreateObject(NUMBER, { 340,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->lives);
		CreateObject(LABEL, { 640,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "COINS");
		CreateObject(IMAGE, { 694,18 }, { 565,490,10,14 }); //image coin
		CreateObject(NUMBER, { 640,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->num_coins);
		CreateObject(LABEL, { 940,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "TIME");
		CreateObject(NUMBER, { 940,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->time_game);
		load_finish = false;
	}
	p2List_item<j1Object*>* item = objects.start;
	while (item != nullptr)
	{
		if (item->data->type == NUMBER)
		{
			j1Label* label_number = (j1Label*)item->data;
			item->data->Draw();
		}

		item = item->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	BROFILER_CATEGORY("GUICleanUp", Profiler::Color::Indigo);
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

void j1Gui::CreateObject(TYPE_OBJECT obj_type, iPoint pos, SDL_Rect rect, SDL_Rect press, SDL_Rect hover, BUTTON_TYPE btn_type, char* label_text, uint* num)
{
	BROFILER_CATEGORY("GUICreateObject", Profiler::Color::PaleTurquoise);
	if (obj_type == LABEL)
	{
		j1Label* label = new j1Label(pos,label_text);

		objects.add(label);

	}
	else if (obj_type == NUMBER)
	{
		j1Label* label_num = new j1Label(pos, num);

		objects.add(label_num);

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
	BROFILER_CATEGORY("GUIOnHover", Profiler::Color::PaleTurquoise);
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
	BROFILER_CATEGORY("GUITriggerFunction", Profiler::Color::HotPink);
	j1Button* button = (j1Button*)obj;

	switch (button->button_type)
	{
	case PLAY:
	{
		game_paused = false;
		CleanUp();
		App->scene->scene_menu = false;
		App->scene->in_game = true;
		App->scene->Start();
		CreateObject(LABEL, { 40,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SCORE");
		CreateObject(NUMBER, { 40,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->score);
		CreateObject(LABEL, { 340,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "LIVES");
		CreateObject(NUMBER, { 340,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->lives);
		CreateObject(LABEL, { 640,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "COINS");
		CreateObject(IMAGE, { 694,18 }, { 565,490,10,14 }); //image coin
		CreateObject(NUMBER, { 640,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->num_coins);
		CreateObject(LABEL, { 940,20 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "TIME");
		CreateObject(NUMBER, { 940,32 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, nullptr, &App->entity_manager->player->time_game);
		break;
	}
	case RESUME:
	{
		game_paused = false;
		App->scene->in_game = true;
		p2List_item<j1Object*>* item = objects.end;
		while (item->data->position.y != 32)
		{
			objects.del(item);
			item = item->prev;
		}
		break;
	}
	case CONTINUE:
	{
		//load_finish = true;
		App->collision->active = true;
		App->entity_manager->active = true;
		
		CleanUp();
		//App->scene->saved = true;
		App->LoadGame();
		//load saved 
		
		break;
	}
	case SETTINGS:
	{
		App->scene->in_game = false;
		CleanUp();
		CreateObject(IMAGE, { 0,0 }, { 0, 240, 1024, 240 }); //background settings menu
		CreateObject(IMAGE, { 575,40 }, { 441, 564, 92, 21 }); //box image behind music
		CreateObject(LABEL, { 596,46 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "MUSIC"); //music text
		CreateObject(BUTTON, { 575,80 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLMINUS); //button volume MINUS
		CreateObject(LABEL, { 580,87 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "-");
		CreateObject(BUTTON, { 637,80 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLPLUS); //button volume PLUS
		CreateObject(LABEL, { 643,87 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "+");

		CreateObject(IMAGE, { 575,120 }, { 441, 564, 92, 21 }); //box image behind fx volume
		CreateObject(LABEL, { 577,126 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "fx volume"); //fx volume text
		CreateObject(BUTTON, { 575,160 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLMINUS); //button volume MINUS
		CreateObject(LABEL, { 580,167 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "-");
		CreateObject(BUTTON, { 637,160 }, { 441,585,21,21 }, { 483,585,21,21 }, { 462,585,21,21 }, VOLPLUS); //button volume PLUS
		CreateObject(LABEL, { 643,167 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "+");
		CreateObject(BUTTON, { 900,200 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, BACK); //button back 
		CreateObject(LABEL, { 926,206 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "BACK"); //text back

		
		break;
	}
	case CREDITS:
	{
		App->scene->in_game = false;
		CleanUp();
		CreateObject(IMAGE, { 0,0 }, { 0, 240, 1024, 240 }); //background settings menu

		CreateObject(BUTTON, { 900,200 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, BACK); //button back 
		CreateObject(LABEL, { 926,206 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "BACK"); //text back

		CreateObject(IMAGE, { 440,30 }, { 0, 882, 451, 171 });
		break;
	}
	case EXIT:
	{
		exit(0);
		break;
	}
	case BACK:
	{
		App->scene->in_game = false;
		CleanUp();
		//Start();
		CreateObject(IMAGE, { 0,0 }, { 0, 0, 1024, 240 }); //background image intro menu
		CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
		CreateObject(IMAGE, { 570,27 }, { 325,480,116,150 }); //box image below buttons intro menu
		CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
		CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu

		//buttons intro menu 
		CreateObject(BUTTON, { 582,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, PLAY); //button start 
		CreateObject(LABEL, { 605,50 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start
		CreateObject(BUTTON, { 582,68 }, { 441,543,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CONTINUE); //button unclickable continue 
		CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CONTINUE");//text continue
		CreateObject(BUTTON, { 582,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
		CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SETTINGS");//text settings
		CreateObject(BUTTON, { 582,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
		CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
		CreateObject(BUTTON, { 582,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, EXIT); //button exit 
		CreateObject(LABEL, { 611,146 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "EXIT");//text exit*
		CreateObject(BUTTON, { 582,182 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, WEBSITE); //button web 
		CreateObject(LABEL, { 594,188 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "WEBSITE");//text web
		break;
	}
	case SAVEANDEXIT:
	{
		game_paused = false;
		App->scene->in_game = false;
		App->scene->scene_menu = true;
		save_exit_menu = true;
		//App->entity_manager->active = false;
		App->audio->StopMusic();
		App->audio->PlayMusic("audio/music/intro.ogg");


		CleanUp();
		//App->entity_manager->DestroyEntities();
		//Start();
		//TODO save and delete everything in game to return to main menu and when clicked continue load the game

		//App->entity_manager->DestroyEntities();
		/*CreateObject(IMAGE, { 0,0 }, { 0, 0, 1024, 240 }); //background image intro menu
		CreateObject(IMAGE, { 100,20 }, { 0,480, 325,162 }); //title image into menu
		CreateObject(IMAGE, { 570,27 }, { 325,480,116,150 }); //box image below buttons intro menu
		CreateObject(IMAGE, { 753,145 }, { 533,490,16,32 }); //mario intro menu
		CreateObject(IMAGE, { 900,192 }, { 549,490,16,16 }); //goomba intro menu

															 //buttons intro menu 
		CreateObject(BUTTON, { 582,44 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, PLAY); //button start 
		CreateObject(LABEL, { 605,50 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "START"); //text start
		CreateObject(BUTTON, { 582,68 }, { 441,543,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CONTINUE); //button unclickable continue 
		CreateObject(LABEL, { 589,74 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CONTINUE");//text continue
		CreateObject(BUTTON, { 582,92 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, SETTINGS); //button settings 
		CreateObject(LABEL, { 590,98 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "SETTINGS");//text settings
		CreateObject(BUTTON, { 582,116 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, CREDITS); //button credits 
		CreateObject(LABEL, { 594,122 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "CREDITS");//text credits
		CreateObject(BUTTON, { 582,140 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, EXIT); //button exit 
		CreateObject(LABEL, { 611,146 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "EXIT");//text exit*
		CreateObject(BUTTON, { 582,182 }, { 441,480,92,21 }, { 441,522,92,21 }, { 441,501,92,21 }, WEBSITE); //button web 
		CreateObject(LABEL, { 594,188 }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, { NULL,NULL,NULL,NULL }, NONE, "WEBSITE");//text web*/
		break;
	}
	case WEBSITE: 
	{
		ShellExecute(NULL, "open", "https://manavld.github.io/OwnMarioBros/", NULL, NULL, SW_SHOWNORMAL);
		break;
	}
	case VOLMINUS:
	{
		App->audio->VolumeMinus();
		break;
	}
	case VOLPLUS:
	{
		App->audio->VolumePlus();
		break;
	}
	default:
		break;
	}
	SDL_SetTextureAlphaMod(App->gui->atlas, 255);
	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

