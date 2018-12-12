#pragma once
#ifndef j1Object_H_
#define j1Object_H_

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "p2SString.h"

enum TYPE_OBJECT
{
	LABEL,
	IMAGE,
	BUTTON,
	UKNOWN
};

class Object
{
public:

	p2SString label_text;
	fPoint position;
	SDL_Rect atlas_pos;

	//_TTF_Font* font;
};
#endif // !j1Object_H_

