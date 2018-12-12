#ifndef __j1GUI_H__
#define __j1GUI_H__

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

	bool Update(float dt);
	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	void CreateObject(TYPE_OBJECT ob, fPoint pos, SDL_Rect rect);
	void DeleteObject(Object ob);

	//virtual Blit();

	const SDL_Texture* GetAtlas() const;

	p2List<Object*> objects;
	SDL_Texture* atlas;
	//j1Label label;

private:

	Object obj;

	p2SString atlas_file_name;
};

#endif // __j1GUI_H__