#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_parser.h>
#include <stdio.h>
#include <stdlib.h>

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

void	change_map(t_app *cbd)
{
	cbd->mapdata = load_map(cbd->mapdata, cbd->menudata->select_menu.current_item);
	if (!cbd->mapdata)
	{
		cbd_error(ERR_LOAD_MAP);
		exit(1);
	}
	printf("Map Loaded succesfully!\n");
	cbd->menudata->state = MAIN;
	init_playerdata(&cbd->playerdata, cbd->mapdata);
	set_menu_state(cbd->menudata, MAIN);
}
