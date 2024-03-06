#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <cbd_render.h>

void	move_player(void *param)
{
	t_app *cbd;

	cbd = param;
	float move_speed = cbd->mlx->delta_time * 2;

	t_vec_f pos;
	t_vec_f dir;

	pos = vec_assign(cbd->playerdata.pos.x, cbd->playerdata.pos.y);
	dir = vec_assign(cbd->playerdata.dir.x, cbd->playerdata.dir.y);

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))
	{
		int x = (pos.x + dir.x * move_speed);
		int y = (pos.y + dir.y * move_speed);
		if (cbd->mapdata->cbd_map[(int)pos.y][x] == '0')
			cbd->playerdata.pos.x += cbd->playerdata.dir.x * move_speed;
		if (cbd->mapdata->cbd_map[y][(int)pos.x] == '0')
			cbd->playerdata.pos.y += cbd->playerdata.dir.y * move_speed;
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
	{
		int x = (pos.x - dir.x * move_speed);
		int y = (pos.y - dir.y * move_speed);
		if (cbd->mapdata->cbd_map[(int)pos.y][x] == '0')
			cbd->playerdata.pos.x -= cbd->playerdata.dir.x * move_speed;
		if (cbd->mapdata->cbd_map[y][(int)pos.x] == '0')
			cbd->playerdata.pos.y -= cbd->playerdata.dir.y * move_speed;
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= cbd->mapdata->width)
	{
		vec_rotate(&cbd->playerdata.dir, cbd->mlx->delta_time * 3);
		vec_rotate(&cbd->playerdata.plane, cbd->mlx->delta_time * 3);
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
	{
		vec_rotate(&cbd->playerdata.dir, -cbd->mlx->delta_time * 3);
		vec_rotate(&cbd->playerdata.plane, -cbd->mlx->delta_time * 3);
	}
	draw_grid(cbd, cbd->mapdata->width, cbd->mapdata->height);
}

bool	cbd_main(t_app *cbd)
{
	printf("Init\n");
	if (cbd_init(cbd))
		return (FAILURE);
	printf("Init success\n");
	mlx_loop(cbd->mlx);
	mlx_terminate(cbd->mlx);
	cleanup(cbd);
	return (SUCCESS);
}
