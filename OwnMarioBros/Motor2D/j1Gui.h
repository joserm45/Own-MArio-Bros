#ifndef _j1GUI_H_
#define _j1GUI_H_

#include "j1Module.h"
#include "j1Fonts.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Object.h"
#include "j1Label.h"
#include "SDL\include\SDL.h"
#include "SDL/include/SDL_pixels.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
struct SDL_Rect;
struct SDL_Texture;

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	void CreateObject(TYPE_OBJECT obj, iPoint pos, SDL_Rect rect, char* label_text = nullptr);
	void DeleteObject(j1Object* obj);

	//virtual Blit();

	SDL_Texture* GetAtlas() const;

public:

	p2List<j1Object*> objects;
	SDL_Texture* atlas;

private:

	p2SString atlas_file_name;
};

#endif // __j1GUI_H__