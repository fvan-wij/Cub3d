#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <cbd_render.h>


t_vec	cast_ray(char **map, t_vec pos, t_vec_f dir)
{
	t_vec wall;
	t_vec_f side_dist;
	t_vec_f delta_dist;
	t_vec_f step_size;
	t_vec	map_check;
	t_vec	step;
	t_vec_f ray_len;

	(void) map;
	(void) side_dist;
	(void) delta_dist;
	(void) dir;

	step_size.x = sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x));
	step_size.y = sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y));
	map_check = pos;
	if (dir.x < 0)
	{
		step.x = -1;
		ray_len.x = (pos.x - (float)map_check.x) * step_size.x;
	}
	else
	{
		step.x = 1;
		ray_len.x = (((float)map_check.x + 1) - pos.x) * step_size.x;
	}
	if (dir.y < 0)
	{
		step.y = -1;
		ray_len.y = (pos.y - (float)map_check.y) * step_size.y;
	}
	else
	{
		step.y = 1;
		ray_len.y = (((float)map_check.y + 1) - pos.y) * step_size.x;
	}


	bool wall_is_found = false;
	float max_dist = 100.0f;
	float dist = 0;
	while (!wall_is_found && dist < max_dist)
	{
		if (ray_len.x < ray_len.y)
		{
			map_check.x += step.x;
			dist = ray_len.x;
			ray_len.x += step_size.x;
		}
		else
		{
			map_check.y += step.y;
			dist = ray_len.y;
			ray_len.y += step_size.y;
		}

		if (map_check.y >= 0 && map_check.y < 16 && map_check.x >= 0 && map_check.x < 16)
		{
			if (map[map_check.y][map_check.x] == '1')
				wall_is_found = true;
		}
	}

	if (wall_is_found)
	{
		wall.x = pos.x + dir.x * dist;
		wall.y = pos.y + dir.y * dist;
		return (wall);
	}


	// while (map[pos.y][pos.x])
	// {
	// 	printf("pos(%d, %d)\n", pos.x, pos.y);
	// 	if (map[pos.y][pos.x] == '1')
	// 	{
	// 		wall.x = pos.x;
	// 		wall.y = pos.y;
	// 		printf("wall(%d, %d)\n", wall.x, wall.y);
	// 		return (wall);
	// 	}
	// 	pos.y--;
	// }
	return (pos);
}
