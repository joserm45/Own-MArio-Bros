#pragma once
#ifndef j1Label_H__
#define j1Label_H__
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1App.h"

struct SDL_Texture;

class j1Label : public j1Object
{
public:

	j1Label();
	j1Label(iPoint pos, char* label_text);
	virtual ~j1Label();

	void Start();
	void Draw();

public:

	
};

#endif // !j1Label_H__
