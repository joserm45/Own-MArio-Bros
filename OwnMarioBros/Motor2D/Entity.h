#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "j1App.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Entity
{
public:
	Entity(float x, float y);
	virtual ~Entity();

	const Collider* GetCollider() const;
	virtual bool Update(float dt);
	virtual void Draw();
	virtual bool Save(pugi::xml_node&) const;
	virtual bool Load(pugi::xml_node&);
	virtual void LoadAnimation();
	virtual void Input(float dt);
	virtual void OnCollision(Collider* a, Collider* b);

public:
	fPoint position;
	ENTITY_TYPE entity_type;
	SDL_Texture* sprite = nullptr;
	Collider* collider = nullptr;
	Animation* animation = nullptr;
};




#endif
