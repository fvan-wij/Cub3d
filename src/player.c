#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>

void	attack_player(t_entity *ent, t_player *playerdata, t_fx *fx)
{
	fx->crt = true;
	fx->crt_timer = 100;
	playerdata->health -= ent->damage;
	playerdata->i_time = 3;
}

void	update_player(t_player *playerdata, t_app *cbd)
{
	if (playerdata->i_time > 0)
	{
		playerdata->i_time -= cbd->mlx->delta_time;
	}
	if (playerdata->health < 1)
		set_menu_state(cbd->menudata, GAME_OVER);
}

void	escape_player(t_vec2d pos, t_vec2d dir, t_app *cbd)
{
	const char **map = (const char**) cbd->mapdata->cbd_map;
	t_vec2d potential_pos = vec_add(pos, dir);

	if (map[(int)potential_pos.y][(int)potential_pos.x] == '3')
		set_menu_state(cbd->menudata, GAME_WON);
}
