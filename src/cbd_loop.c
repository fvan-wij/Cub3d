#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>

void	cbd_loop(void *param)
{
	t_app *cbd;

	cbd = param;
	if (cbd->menudata->state == OFF)
	{
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		move_player(cbd);
		update_entities(cbd);
		move_entities(cbd->mapdata->entities, cbd);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
	{
		change_map(cbd);
	}
	if (cbd->render.b_timer)
	{
		cbd->render.timer -= cbd->mlx->delta_time * 1000;
	}
	if (cbd->render.timer < 0)
	{
		cbd->render.timer = 75;
		cbd->render.b_timer = false;
	}
}
