#ifndef _j1SLIDER_H
#define _j1SLIDER_H
#include"j1App.h"
#include "j1Gui.h"

enum TYPE_SLIDER
{
	VERTICAL,
	HORIZONTAL
};

class j1Slider : public j1Object
{
public:
	j1Slider();
	j1Slider(iPoint, SDL_Rect, char* label_text);
	~j1Slider();

	void Draw();
	void OnDrag(j1Object * obj);
	
private:
	TYPE_SLIDER type_slider;
	uint max;
	uint min;
	iPoint prev_mouse;

};



#endif 