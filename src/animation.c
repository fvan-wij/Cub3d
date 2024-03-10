#include <cub3d.h>
#include <MLX42.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	shoot_weapon(mlx_t	*mlx, t_inventory *inv)
{
	t_animation *fire_animation = inv->weapons[inv->equipped].fire_animation;

	if (fire_animation->loop)
	{
		inv->weapons[inv->equipped].fire_animation->loop = true;
		fire_animation->total_time += mlx->delta_time * 100;
		inv->weapons[inv->equipped].img->enabled = false;
		int current_frame = (int) (fire_animation->total_time / fire_animation->frames[0].duration);
		
		printf("current_Frame: %d\n", current_frame);
		if (current_frame == 1)
			inv->weapons[inv->equipped].fire_animation->frames[0].img->enabled = true;
		else
			inv->weapons[inv->equipped].fire_animation->frames[0].img->enabled = false;
		if (current_frame == 2)
			inv->weapons[inv->equipped].fire_animation->frames[1].img->enabled = true;
		else
			inv->weapons[inv->equipped].fire_animation->frames[1].img->enabled = false;
		if (current_frame == 3)
			inv->weapons[inv->equipped].fire_animation->frames[2].img->enabled = true;
		else
			inv->weapons[inv->equipped].fire_animation->frames[2].img->enabled = false;
		if (current_frame > MAX_FRAMES)
		{
			inv->weapons[inv->equipped].fire_animation->frames[0].img->enabled = false;
			inv->weapons[inv->equipped].fire_animation->frames[1].img->enabled = false;
			inv->weapons[inv->equipped].fire_animation->frames[2].img->enabled = false;
			inv->weapons[inv->equipped].fire_animation->total_time = 0;
			inv->weapons[inv->equipped].fire_animation->loop = false;
			inv->weapons[inv->equipped].img->enabled = true;
		}
	}
	else
	{
		inv->weapons[inv->equipped].fire_animation->loop = false;
		inv->weapons[inv->equipped].fire_animation->frames[0].img->enabled = false;
		inv->weapons[inv->equipped].fire_animation->frames[1].img->enabled = false;
		inv->weapons[inv->equipped].fire_animation->frames[2].img->enabled = false;
		inv->weapons[inv->equipped].img->enabled = true;
	}
}
