#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <cbd_render.h>
#include <math.h>

void	move_player(void *param)
{
	t_app *cbd;

	cbd = param;
	float move_speed = cbd->mlx->delta_time * 2;
	float headbob_speed = cbd->mlx->delta_time * 10;

	t_vec_f pos;
	t_vec_f dir;

	pos = vec_assign(cbd->playerdata.pos.x, cbd->playerdata.pos.y);
	dir = vec_assign(cbd->playerdata.dir.x, cbd->playerdata.dir.y);

	//Shift multiplier
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT_SHIFT))
	{
		move_speed *= 2;
		headbob_speed *= 2;
	}
	if (cbd->hud->img[HUD_HANDS]->enabled && cbd->playerdata.map_peak > -100)
		cbd->playerdata.map_peak -= cos(cbd->mlx->delta_time) * 2;
	else if (cbd->playerdata.map_peak < 0)
		cbd->playerdata.map_peak += cos(cbd->mlx->delta_time) * 2;

	t_vec_f potential_pos = pos;
	t_vec_f local_pos = {pos.x - (int) pos.x, pos.y - (int) pos.y};
	char U = cbd->mapdata->cbd_map[(int)pos.y - 1][(int)pos.x];
	char R = cbd->mapdata->cbd_map[(int)pos.y][(int)pos.x + 1];
	char D = cbd->mapdata->cbd_map[(int)pos.y + 1][(int)pos.x];
	char L = cbd->mapdata->cbd_map[(int)pos.y][(int)pos.x - 1];

	//Wipe screen

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))
	{
		float r = vec_length(dir) / 8; //Radius of circle
		potential_pos.x = pos.x + dir.x * move_speed;
		potential_pos.y = pos.y + dir.y * move_speed;
		cbd->playerdata.headbob += headbob_speed;
		if (cbd->playerdata.headbob > 2 * M_PI)
			cbd->playerdata.headbob = 0;
		if (local_pos.x <= 0.5 && L == '1')
		{
			float dl = local_pos.x;
			if (dl <= r) // Collision!
			{
				float overlap = r - dl;
				// printf("overlap_dl: %f\n", overlap);
				potential_pos.x = potential_pos.x + overlap;
			}
		}
		if (local_pos.y >= 0.5 && D == '1')
		{
			float dd = 1 - local_pos.y;
			if (dd <= r) // Collision!
			{
				float overlap = r - dd;
				// printf("overlap_dd: %f\n", overlap);
				potential_pos.y = potential_pos.y - overlap;
			}
		}
		if (local_pos.y <= 0.5 && U == '1')
		{
			float du = local_pos.y;
			if (du <= r) // Collision!
			{
				float overlap = r - du;
				// printf("overlap_du: %f\n", overlap);
				potential_pos.y = potential_pos.y + overlap;
			}
		}
		if (local_pos.x >= 0.5 && R == '1')
		{
			float dr = 1 - local_pos.x;
			if (dr <= r) // Collision!
			{
				float overlap = r - dr;
				// printf("overlap_dr: %f\n", overlap);
				potential_pos.x = potential_pos.x - overlap;
			}
		}
	}
	else if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
	{
		potential_pos.x = pos.x - dir.x * move_speed;
		potential_pos.y = pos.y - dir.y * move_speed;
		cbd->playerdata.headbob += headbob_speed;
		if (cbd->playerdata.headbob > 2 * M_PI)
			cbd->playerdata.headbob = 0;
		float r = vec_length(dir) / 8; //Radius of circle
		if (local_pos.x <= 0.5 && L == '1')
		{
			float dl = local_pos.x;
			if (dl <= r) // Collision!
			{
				float overlap = r - dl;
				// printf("overlap_dl: %f\n", overlap);
				potential_pos.x = potential_pos.x + overlap;
			}
		}
		if (local_pos.y >= 0.5 && D == '1')
		{
			float dd = 1 - local_pos.y;
			if (dd <= r) // Collision!
			{
				float overlap = r - dd;
				// printf("overlap_dd: %f\n", overlap);
				potential_pos.y = potential_pos.y - overlap;
			}
		}
		if (local_pos.y <= 0.5 && U == '1')
		{
			float du = local_pos.y;
			if (du <= r) // Collision!
			{
				float overlap = r - du;
				// printf("overlap_du: %f\n", overlap);
				potential_pos.y = potential_pos.y + overlap;
			}
		}
		if (local_pos.x >= 0.5 && R == '1')
		{
			float dr = 1 - local_pos.x;
			if (dr <= r) // Collision!
			{
				float overlap = r - dr;
				// printf("overlap_dr: %f\n", overlap);
				potential_pos.x = potential_pos.x - overlap;
				// potential_pos.y = potential_pos.y - overlap;
			}
		}
	}
	else
	{
		cbd->playerdata.headbob -= cbd->mlx->delta_time;
		if (cbd->playerdata.headbob < 0)
			cbd->playerdata.headbob = 0;
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= cbd->mapdata->width)
	{
		cbd->playerdata.dir = vec_rotate(cbd->playerdata.dir, cbd->mlx->delta_time * 3);
		cbd->playerdata.plane = vec_rotate(cbd->playerdata.plane, cbd->mlx->delta_time * 3);
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
	{
		cbd->playerdata.dir = vec_rotate(cbd->playerdata.dir, -cbd->mlx->delta_time * 3);
		cbd->playerdata.plane = vec_rotate(cbd->playerdata.plane, -cbd->mlx->delta_time * 3);
	}
	cbd->playerdata.pos = potential_pos;
	cbd_render(cbd);
}
