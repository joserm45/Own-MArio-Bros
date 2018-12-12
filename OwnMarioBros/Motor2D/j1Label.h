#pragma once
#ifndef j1Label_H__
#define j1Label_H__
#include "j1Gui.h"
#include "j1Fonts.h"

class j1Label : public Object
{
public:

	j1Label();
	virtual ~j1Label() {};

	void Start();

public:

	_TTF_Font * font;
	j1Fonts* fonts;
};

#endif // !j1Label_H__
