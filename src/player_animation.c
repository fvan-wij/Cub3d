#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <math.h>

t_vec2d	resolve_collision(char **map, t_vec2d pos, t_vec2d dir, t_vec2d potential_pos)
{
	t_vec2d local_pos;
	float r = vec_length(dir) / 8;
	float overlap;

	local_pos.x = pos.x - (int) pos.x;
	local_pos.y = pos.y - (int) pos.y;
	char U = map[(int)pos.y - 1][(int)pos.x];
	char R = map[(int)pos.y][(int)pos.x + 1];
	char D = map[(int)pos.y + 1][(int)pos.x];
	char L = map[(int)pos.y][(int)pos.x - 1];

	if (local_pos.x <= 0.5 && is_wall_bonus(L))
	{
		float dl = local_pos.x;
		if (dl <= r)
		{
			overlap = r - dl;
			potential_pos.x = potential_pos.x + overlap;
		}
	}
	if (local_pos.y >= 0.5 && is_wall_bonus(D))
	{
		float dd = 1 - local_pos.y;
		if (dd <= r)
		{
			overlap = r - dd;
			potential_pos.y = potential_pos.y - overlap;
		}
	}
	if (local_pos.y <= 0.5 && is_wall_bonus(U))
	{
		float du = local_pos.y;
		if (du <= r)
		{
			overlap = r - du;
			potential_pos.y = potential_pos.y + overlap;
		}
	}
	if (local_pos.x >= 0.5 && is_wall_bonus(R))
	{
		float dr = 1 - local_pos.x;
		if (dr <= r)
		{
			overlap = r - dr;
			potential_pos.x = potential_pos.x - overlap;
		}
	}
	return (potential_pos);
}

void	headbob(float *headbob, float speed)
{
	*headbob += speed;
	if (*headbob > 2 * M_PI)
		*headbob = 0;
}

void	reset_player_animation(t_render *render, mlx_t *mlx)
{
	render->headbob -= mlx->delta_time;
	if (render->headbob < 0)
		render->headbob = 0;
}

void	peek_map(t_inventory *inv, t_render *render, mlx_image_t *img, mlx_t *mlx)
{
	inv->weapons[inv->equipped].img->instances[0].x = (cos(render->headbob) * 2) + (WIDTH>>1) - (inv->weapons[inv->equipped].img->width>>1);
	if (render->map_peak < -99)
		render->map_peak = -99;
	if (img->enabled && render->map_peak > -100)
		render->map_peak -= cos(mlx->delta_time) * 2;
	else if (render->map_peak < 0)
		render->map_peak += cos(mlx->delta_time) * 2;
}
