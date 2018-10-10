#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 50

class Animation 
{
public:
	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			loops++;
			current_frame = (loop) ? 0.0f : last_frame - 1;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		loops = 0;
		current_frame = 0;
	}

private:
	int loops = 0;
	float current_frame = 0.0f;
	int last_frame = 0;

	SDL_Rect frames[MAX_FRAMES];

public:
	float speed = 0.25f;
	bool loop = true;

};





#endif
