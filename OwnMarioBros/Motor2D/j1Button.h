#ifndef _j1BUTTON_H
#define _j1BUTTON_H

#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"

class j1Button : public j1Object
{
public:
	j1Button();
	j1Button(iPoint pos, SDL_Rect rect, SDL_Rect pressed, SDL_Rect hover, BUTTON_TYPE btn_type);
	~j1Button();

	void Draw();

	//interaction
	void OnClick(j1Object * obj);
	const bool Trigger(j1Object* obj);

public:

	BUTTON_TYPE button_type;

	SDL_Rect pressed;
	SDL_Rect hover;
};



#endif // !_j1BUTTON_H

