#include "j1Label.h"
#include "j1Fonts.h"

j1Label::j1Label() : Object()
{
	font = fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
}

void j1Label::Start()
{
	font = fonts->Load("fonts\open_sans\OpenSans-Semibold", 12);
}
