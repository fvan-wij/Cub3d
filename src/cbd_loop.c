#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <cbd_audio.h>

void	cbd_loop(void *param)
{
	t_app 	*cbd;
	t_audio *audio;

	cbd = param;
	audio = cbd->audio;
	if (cbd->menudata->state == OFF)
	{
		cbd->elapsed_time += cbd->mlx->delta_time;
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		update_player(&cbd->playerdata, cbd);
		escape_player(cbd->playerdata.pos, cbd->playerdata.dir, cbd);
		move_player(cbd);
		update_entities(cbd);
		move_entities(cbd->mapdata->entities, cbd);
		deal_damage(cbd);
		update_timers(&cbd->render.fx, cbd->mlx->delta_time);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		update_game_audio(audio, cbd->playerdata.inv, cbd->playerdata.state);
		cbd_render(cbd);
	}
	if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
		change_map(cbd);
	update_menu_audio(audio, cbd);
}
