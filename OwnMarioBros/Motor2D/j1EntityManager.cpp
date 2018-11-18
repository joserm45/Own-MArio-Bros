#include "j1EntityManager.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Input.h"
#include "Entity.h"
#include "Brofiler\Brofiler.h"

j1EntityManager::j1EntityManager() : j1Module()
{
	name.create("entities");

}

j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node&)
{
	bool ret = true;
	
	return ret;
}

bool j1EntityManager::Start()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->Start();
		item = item->next;
	}
	
	bool ret = true;
	
	return ret;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("EntityManagerPreUpdate", Profiler::Color::Azure);
	
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->PreUpdate();
		item = item->next;
	}

	bool ret = true;

	return ret;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("EntityManagerUpdate", Profiler::Color::Bisque);
	
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->Update(dt);
		item = item->next;
	}

	bool ret = true;

	return ret;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("EntityManagerPostUpdate", Profiler::Color::BlanchedAlmond);
	
	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		item->data->PostUpdate();
		item = item->next;
	}

	bool ret = true;

	return ret;
}

bool j1EntityManager::CleanUp()
{
	bool ret = true;

	return ret;
}

bool j1EntityManager::Load(pugi::xml_node&)
{
	bool ret = true;

	return ret;
}

bool j1EntityManager::Save(pugi::xml_node&)const
{
	bool ret = true;

	return ret;
}

void j1EntityManager::OnCollision(Collider* a, Collider* b)
{

}

void j1EntityManager::CreateEntity(p2SString name, fPoint position)
{
	if (name == "player")
	{
		if (player != NULL)
		{
			DestroyEntity(player);
		}

		player = new j1Player();

		player->position = position;
		player->Awake();
		player->Start();
		entities.add(player);
	}

	else if (name == "goomba")
	{
		Enemy_Goomba* goomba = new Enemy_Goomba();

		goomba->position = position;
		goomba->Awake();
		goomba->Start();
		entities.add(goomba);
	}

	else if (name == "boo")
	{
		Enemy_Boo* boo = new Enemy_Boo();

		boo->position = position;
		boo->Awake();
		boo->Start();
		entities.add(boo);
	}
	
}

void j1EntityManager::CreateEntities()
{
	p2List_item<Layer*>* iterator;
	p2List_item<Layer*>* layer = nullptr;

	for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logic")
		{
			layer = iterator;
		}
	}

	for (uint i = 0; i < App->map->data.height; i++)
	{
		for (uint j = 0; j < App->map->data.width; j++)
		{
			uint* nextGid = &layer->data->gid[i * App->map->data.width + j];
			if (*nextGid == 621)
			{
				fPoint pos;
				pos.create((float)j * 16, ((float)i * 16));
				App->entity_manager->CreateEntity("player",pos);
			}
			if (*nextGid == 766)
			{
				fPoint pos;
				pos.create((float)j * 16, ((float)i * 16));
				App->entity_manager->CreateEntity("goomba", pos); //commented because goomba move() crashes
			}
			if (*nextGid == 795)
			{
				fPoint pos;
				pos.create((float)j * 16, ((float)i * 16));
				App->entity_manager->CreateEntity("boo", pos);
			}
		}
	}

}

void j1EntityManager::DestroyEntity(Entity * entity)
{
	if (entity != nullptr)
	{
		p2List_item<Entity*>* item = entities.start;

		while (item != NULL)
		{
			if (item->data == entity)
			{

				if (entity->collider != NULL)
				{
					entity->CleanUp();
					RELEASE(entity);
					entities.del(item);
				}

				return;
			}

			item = item->next;
		}
	}
	
}

void j1EntityManager::DestroyEntities()
{
	for (int i = 0; i < entities.count(); i++)
	{
		App->entity_manager->DestroyEntity(entities[i]);
		i--;
	}
}