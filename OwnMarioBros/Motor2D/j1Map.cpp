#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Scene.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{
	
}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	// TODO 5: Prepare the loop to draw all tilesets + Blit

	p2List_item <TileSet*>* data_tilset = data.tilesets.start;
	p2List_item <Layer*>* data_layer = data.layers.start;
	//char * layers = map_file.child("layer").attribute("name").as_string();
	while (data_layer != NULL)
	{
		for (uint x = 0; x < data.width; x++)
		{
			for (uint y = 0; y < data.height; y++)
			{
				iPoint position = MapToWorld(x, y);

				int id = data_layer->data->Get(x, y);

				SDL_Rect rect = data_tilset->data->GetTileRect(id);
				if (data_layer->data->name == "layer_map_lvl1" || data_layer->data->name == "layer_map_lvl2")
				{
					App->render->Blit(data_tilset->data->texture, position.x, position.y, &rect);
					//data_tilset->next;
				}

				else if (data_layer->data->name == "cloud_layer_parallax")
				{
					App->render->Blit(data_tilset->data->texture, position.x - (App->render->camera.x * data_layer->data->parallax_speed), position.y, &rect);
				}

				else if (data_layer->data->name == "logic" && logic != false)
				{
					App->render->Blit(data_tilset->data->texture, position.x - (App->render->camera.x * data_layer->data->parallax_speed), position.y, &rect);
					/*if (id) == 621)
					{
						App->player->position.x = 
					}*/
				}
			}

		}
		data_layer = data_layer->next;
	}
		
		//map_file.child("map").child("layer").next_sibling();
	

}


iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}
iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret;

	ret.x = x / data.tile_width;
	ret.y = y / data.tile_height;

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// TODO 2: clean up all layer data
	// Remove all layers
	p2List_item<TileSet*>* itemm;
	itemm = data.tilesets.start;

	while (itemm != NULL)
	{
		RELEASE(itemm->data);
		itemm = itemm->next;
	}
	data.tilesets.clear();
	
	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	pugi::xml_node root_node;
	for (root_node = map_file.child("map").child("layer"); root_node && ret; root_node = root_node.next_sibling())
	{
		Layer* set = new Layer();

		if (ret == true)
		{
			ret = LoadLayer(root_node, set);
		}
		data.layers.add(set);
		
/*		p2List_item<Layer*>* data_layer = data.layers.start;


		while (data_layer != NULL)
		{
			pugi::xml_document doc;
			pugi::xml_node node;

			pugi::xml_parse_result result = doc.load_file("hello2.tmx");

			node = doc.child("map").child("layer");

			LoadLayer(node,data.layers.start->data);
			data.layers.add(data.layers.start->data):
			*/
		
	  }
	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this vcode with your own variables
		
		p2List_item<Layer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
		{
			Layer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node &node, Layer* layer)
{
	// Node Layer
	// node = node.child("data");
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint();
	layer->height = node.attribute("height").as_uint();

	layer->tile_size = layer->width * layer->height;

	layer->gid = new uint[layer->tile_size];

	memset(layer->gid, 0, layer->tile_size);
	
	pugi::xml_node tile_iteration;

	tile_iteration = node.child("data").child("tile");
	for (uint i = 0; i < layer->tile_size; i++)
	{
		layer->gid[i] = tile_iteration.attribute("gid").as_int();
		tile_iteration = tile_iteration.next_sibling();
	}

	//PARALLAX

	for (pugi::xml_node it = node.child("properties").child("property"); it != NULL; it = it.next_sibling())
	{
		p2SString layer_name = it.attribute("name").as_string();

		if (layer_name == "Parallax")
		{
			layer->parallax_speed = it.attribute("value").as_float();
		}
		if (layer_name == "Colliders")
		{
			layer->iscollision = it.attribute("value").as_bool();
		}

	}

	return true;
}

//TODO 3: Create the definition for a function that loads a single layer
//bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
//{
//}
void j1Map::UnloadMap()
{
	data.tilesets.clear();
	data.layers.clear();
}

inline uint Layer::Get(int x, int y) const
{
	return  gid[width * y + x];
}

Layer::~Layer()
{
	if (gid != nullptr)
	{
		delete[]gid;
	}
}

bool j1Map::Walkability()
{

	bool ret = true;
	int player_x = App->player->position.x / 16; //check next tile right
	int player_y = (App->player->position.y + 16) / 16;

	p2List_item<Layer*>* iterator;
	p2List_item<Layer*>* layer = nullptr;

	for (iterator = data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logic")
		{
			layer = iterator;
		}
	}

	//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
	uint* nextGid = &layer->data->gid[ player_x + player_y * layer->data->width ];

	if (App->player->status == RIGHT)
	{
		nextGid++;
		if (*nextGid == 650)
			ret = false;
		else if (*nextGid != 650)
			ret = true;
		if (*nextGid == 708)
		{
			if (App->scene->current_lvl == 1)
			{
				lvl1_complete = true;
				init_timer = true;
			}
			if (App->scene->current_lvl == 2)
			{
				lvl2_complete = true;
				init_timer = true;
			}
		}
			
	}
	else if (App->player->status == LEFT)
	{
		nextGid;
		if (*nextGid == 650)
			ret = false;
		else if (*nextGid != 650)
			ret = true;
	}


	return ret;
}
void j1Map::LoadPlayerFromTiled()
{

}

/*int GetX() const
{
	return x;
}

int GetY() const
{
	return 0;
}*/
