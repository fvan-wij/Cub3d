#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <cbd_render.h>

long	absolute(long value)
{
	if (value < 0)
		return (-value);
	return (value);
}

t_vec_f	cast_ray(char **map, t_player p, int x)
{
	double camera_x = 2 * x / (double) 30 - 1;
	printf("Camera_x: %f\n", camera_x);
	t_vec	vec_map;
	t_vec_f side_dist;
	t_vec_f	delta_dist;
	double	perp_wall_dist;
	t_vec	step;
	bool	hit = false;
	int		side;

	vec_map.x = (int)p.pos.x;
	vec_map.y = (int)p.pos.y;


	p.rays[0].ray_dir.x = p.dir.x + p.plane.x * camera_x;
	p.rays[0].ray_dir.y = p.dir.y + p.plane.y * camera_x;
	printf("ray_dir(%f, %f)\n", p.rays[0].ray_dir.x, p.rays[0].ray_dir.y);

	delta_dist.x = (p.rays[0].ray_dir.x == 0) ? 1e30 : fabs(1 / p.rays[0].ray_dir.x);
	delta_dist.y = (p.rays[0].ray_dir.y == 0) ? 1e30 : fabs(1 / p.rays[0].ray_dir.y);

	if (p.rays[0].ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (p.pos.x - vec_map.x) * delta_dist.x;
	}
	else 
	{
		step.x = 1;
		side_dist.x = (vec_map.x + 1.0 - p.pos.x) * delta_dist.x;
	}
	if (p.rays[0].ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (p.pos.y - vec_map.y) * delta_dist.y;
	}
	else 
	{
		step.y = 1;	
		side_dist.y = (vec_map.y + 1.0 - p.pos.y) * delta_dist.y;
	}

	while(!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			vec_map.x += step.x;
			side = 0;
		}
		else 
		{
			side_dist.y += delta_dist.y;
			vec_map.y += step.y;
			side = 1;
		}

		if (vec_map.x >= 0 && vec_map.x < 16 && vec_map.y >= 0 && vec_map.y < 16 && map[vec_map.y][vec_map.x] == '1')
			hit = true;
	}
	if (side == 0)
		perp_wall_dist = (side_dist.x - delta_dist.x);
	else 
		perp_wall_dist = (side_dist.y - delta_dist.y);

	t_vec_f	intersection;

	intersection.x = (p.pos.x + (p.rays[0].ray_dir.x * perp_wall_dist)) * TILESIZE; 
	intersection.y = (p.pos.y + (p.rays[0].ray_dir.y * perp_wall_dist)) * TILESIZE;
	printf("intersection(%f, %f)\n", intersection.x, intersection.y);

	return (intersection);
}
