#include <cub3d.h>
#include <MLX42.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	update_animation(mlx_t *mlx, t_weapon *weapon)
{
	int current_frame;

	current_frame = (int) (weapon->fire_animation->total_time / weapon->fire_animation->frames[0].duration);
	weapon->fire_animation->total_time += mlx->delta_time * 15;
	if (current_frame == 1)
		weapon->fire_animation->frames[0].img->enabled = true;
	else
		weapon->fire_animation->frames[0].img->enabled = false;
	if (current_frame == 2)
		weapon->fire_animation->frames[1].img->enabled = true;
	else
		weapon->fire_animation->frames[1].img->enabled = false;
	if (current_frame == 3)
		weapon->fire_animation->frames[2].img->enabled = true;
	else
		weapon->fire_animation->frames[2].img->enabled = false;
	if (current_frame > MAX_FRAMES)
	{
		weapon->fire_animation->frames[0].img->enabled = false;
		weapon->fire_animation->frames[1].img->enabled = false;
		weapon->fire_animation->frames[2].img->enabled = false;
		weapon->fire_animation->total_time = 0;
		weapon->fire_animation->loop = false;
	}
}

void	reset_animation(t_weapon *current_weapon)
{
		current_weapon->fire_animation->loop = false;
		current_weapon->fire_animation->frames[0].img->enabled = false;
		current_weapon->fire_animation->frames[1].img->enabled = false;
		current_weapon->fire_animation->frames[2].img->enabled = false;
		current_weapon->img->enabled = true;
}

void	play_weapon_animation(mlx_t	*mlx, t_inventory *inv)
{
	t_weapon *weapon;

	weapon = &inv->weapons[inv->equipped];
	if (weapon->fire_animation->loop)
	{
		inv->weapons[inv->equipped].img->enabled = false;
		update_animation(mlx, weapon);
	}
	else
		reset_animation(&inv->weapons[inv->equipped]);
}
