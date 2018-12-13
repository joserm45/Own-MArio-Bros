#ifndef j1Image_H__
#define j1Image_H__
#include"j1App.h"
#include "j1Gui.h"

class j1Image : public j1Object
{
public:

	j1Image();
	j1Image(iPoint,SDL_Rect);
	~j1Image();

	void Draw();
public:

	
	/*iPoint position = { 0,0 };
	SDL_Rect rect = { 0,0,0,0 };*/

};


#endif // !j1Image_H__
