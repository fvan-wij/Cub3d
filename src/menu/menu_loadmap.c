#include "cbd_audio.h"
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_map	*load_map(t_map *curr_map, uint8_t	map_id)
{
	t_map *new_map;

	cleanup_map(curr_map);
	curr_map = NULL;
	new_map = ft_calloc(1, sizeof(t_map));
	if (map_id == BTN_DARK_SECRET)
		new_map = cbd_parse_map("./data/maps/dark_secret.cub");
	if (map_id == BTN_THE_BUNKER)
		new_map = cbd_parse_map("./data/maps/the_bunker.cub");
	if (map_id == BTN_RABBIT_HOLE)
		new_map = cbd_parse_map("./data/maps/rabbit_hole.cub");
	if (map_id == BTN_SNOW_CRASH)
		new_map = cbd_parse_map("./data/maps/snow_crash.cub");
	if (map_id == BTN_CONFRONTATION)
		new_map = cbd_parse_map("./data/maps/confrontation.cub");
	if (!new_map)
		return (NULL);
	return (new_map);
}

void	reset_inventory(t_inventory *inv)
{
	reset_animation(&inv->weapons[WPN_CHAINSAW]);
	// inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
	// inv->weapons[WPN_CHAINSAW].fire_animation->enabled = false;
	// inv->weapons[WPN_CHAINSAW].fire_animation->current_frame = 0;
	inv->weapons[WPN_MAP].in_inventory = false;
	inv->weapons[WPN_CHAINSAW].in_inventory = false;
	inv->weapons[WPN_CHAINSAW].ammo = 0;
	inv->equipped = WPN_FIST;
}

void	respawn(t_app *cbd)
{
	t_audio		*audio;
	t_entity	*curr;

	audio = cbd->audio;
	if (cbd->checkpoint)
	{
		cbd->playerdata.pos = vec_assign(13.5, 2.5);
		cbd->playerdata.dir = vec_assign(-1.0, 0.0);
		cbd->playerdata.plane = vec_rotate(cbd->playerdata.dir, M_PI / 2);
		cbd->mapdata->cbd_map[13][2] = '4';
		cbd->playerdata.health = 5;
		audio->enemy->health = 100;
		cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo = cbd->checkpoint_state.ammo;
		audio->enemy->animation.current_animation = 0;
		audio->enemy->pos = audio->enemy->destinations[0];
		audio->enemy->limb = 0;
		audio->enemy->speed = 1.5;
		curr = cbd->mapdata->entities;
		while (curr->next != NULL)
		{
			if (curr->type == ENTITY_ITEM && ft_strncmp(curr->name, "chainsaw", 8) != 0)
				curr->enabled = true;
			curr = curr->next;
		}
	}
	else
	{
		cbd->mapdata = load_map(cbd->mapdata, LVL_DARK_SECRET);
		if (!cbd->mapdata)
		{
			cbd_error(ERR_LOAD_MAP);
			exit(1);
		}
		audio->near_death = false;
		reset_inventory(cbd->playerdata.inv);
		init_playerdata(&cbd->playerdata, cbd->mapdata);
	}

}

void	change_map(t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	audio->trigger1 = NULL;
	audio->tv = NULL;
	audio->enemy = NULL;
	audio->vc = NULL;
	audio->near_death = false;
	cbd->mapdata = load_map(cbd->mapdata, cbd->menudata->select_menu.current_item);
	if (!cbd->mapdata)
	{
		cbd_error(ERR_LOAD_MAP);
		exit(1);
	}
	printf("Map Loaded successfully!\n");
	cbd->menudata->state = MAIN;
	reset_inventory(cbd->playerdata.inv);
	init_playerdata(&cbd->playerdata, cbd->mapdata);
	set_menu_state(cbd->menudata, MAIN);
}
