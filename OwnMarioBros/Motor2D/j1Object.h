#pragma once
#ifndef _j1Object_H_
#define _j1Object_H_

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Input.h"

enum TYPE_OBJECT
{
	LABEL,
	IMAGE,
	BUTTON,
	UKNOWN
};

enum BUTTON_TYPE
{
	PLAY,
	CONTINUE,
	SETTINGS,
	CREDITS,
	EXIT,
	RESUME,
	BACK,
	SAVEANDRESUME,
	SAVEANDEXIT,
	NONE
};

class j1Object
{
public:

	j1Object();
	virtual ~j1Object();

	virtual void Start();

	void Update(float dt);

	virtual void Draw();
	virtual void OnClick(j1Object * obj);
	const bool GuiTrigger(j1Object* obj);


	TYPE_OBJECT type = UKNOWN;

	iPoint position = { 0, 0};
	iPoint camera_pos = { 0,0 };

	SDL_Rect atlas_pos = { 0,0,0,0 };

	bool mouse_hover = false;
	bool clicked = false;
	bool active = false;
	//_TTF_Font* font;
};
#endif // !j1Object_H_

