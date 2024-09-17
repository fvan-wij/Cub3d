#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>
#include <cbd_audio.h>
#include <cbd_error.h>

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
	{
		set_menu_state(cbd->menudata, GAME_OVER);
		if (cbd->menudata->state == GAME_OVER)
			respawn(cbd);
	}
}

void	escape_player(t_vec2d pos, t_vec2d dir, t_app *cbd)
{
	t_audio 	*audio;
	const char 	**map = (const char**) cbd->mapdata->cbd_map;
	t_vec2d 	potential_pos = vec_add(pos, dir);

	if (map[(int)potential_pos.y][(int)potential_pos.x] == '3')
	{
		set_menu_state(cbd->menudata, GAME_WON);
		audio = cbd->audio;
		audio->trigger1 = NULL;
		audio->tv = NULL;
		audio->enemy = NULL;
		audio->checkpoint = false;
		cbd->mapdata = load_map(cbd->mapdata, LVL_DARK_SECRET);
		if (!cbd->mapdata)
		{
			cbd_error(ERR_LOAD_MAP);
			exit(1);
		}
		reset_inventory(cbd->playerdata.inv);
		init_playerdata(&cbd->playerdata, cbd->mapdata);
	}
}
