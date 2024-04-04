#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>

void	attack_player(t_entity *ent, t_player *playerdata)
{
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
	{
		set_menu_state(cbd->menudata, GAME_OVER);
	}
}