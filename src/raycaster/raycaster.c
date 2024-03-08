#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

t_ray	cast_ray(char **map, t_player p, int x)
{
	t_ray	ray;
	double camera_x = (double)(2.0 * x / WIDTH) - 1;
	t_vec2i	vec_map;
	t_vec2d side_dist;
	t_vec2d	delta_dist;
	double	perp_wall_dist;
	t_vec2i	step;
	bool	hit = false;
	int		side;

	vec_map.x = (int)p.pos.x;
	vec_map.y = (int)p.pos.y;

	ray.dir.x = p.dir.x + (p.plane.x * camera_x);
	ray.dir.y = p.dir.y + (p.plane.y * camera_x);
	// printf("ray_dir(%f, %f)\n", ray.dir.x, ray.dir.y);

	delta_dist.x = (ray.dir.x == 0) ? 1e30 : fabs(1 / ray.dir.x);
	delta_dist.y = (ray.dir.y == 0) ? 1e30 : fabs(1 / ray.dir.y);

	if (ray.dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (p.pos.x - vec_map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (vec_map.x + 1.0 - p.pos.x) * delta_dist.x;
	}
	if (ray.dir.y < 0)
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

	// t_vec2d	intersection;

	ray.side = side;
	ray.wall_dist = perp_wall_dist;
	ray.intersection.x = (p.pos.x + (ray.dir.x * perp_wall_dist)) * TILESIZE;
	ray.intersection.y = (p.pos.y + (ray.dir.y * perp_wall_dist)) * TILESIZE;

	return (ray);
}

void	cast_rays(char **map, t_player *p)
{
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		p->rays[i] = cast_ray(map, *p, i);
		i++;
	}
}
