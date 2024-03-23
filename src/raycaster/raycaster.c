#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


/*
Needs:
	A context (The map)
	A position
	A direction
*/
t_ray	raycast(char **map, t_vec2d pos, t_vec2d dir)
{
	t_ray	ray;
	t_vec2i	vec_map;
	t_vec2d side_dist;
	t_vec2d	delta_dist;
	double	perp_wall_dist;
	t_vec2i	step;
	bool	hit = false;

	ray.dir = dir;
	vec_map.x = (int)pos.x;
	vec_map.y = (int)pos.y;

	// calculate step, initial side_dist and delta_dist
	delta_dist.x = (ray.dir.x == 0) ? 1e30 : fabs(1 / ray.dir.x);
	delta_dist.y = (ray.dir.y == 0) ? 1e30 : fabs(1 / ray.dir.y);
	if (ray.dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (pos.x - vec_map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (vec_map.x + 1.0 - pos.x) * delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (pos.y - vec_map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (vec_map.y + 1.0 - pos.y) * delta_dist.y;
	}
	// perform DDA (raycast loop)
	while(!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			vec_map.x += step.x;
			ray.side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			vec_map.y += step.y;
			ray.side = 1;
		}
		if (map[vec_map.y][vec_map.x] && vec_map.x >= 0 && vec_map.y >= 0 && (is_wall_bonus(map[vec_map.y][vec_map.x])))
			hit = true;
	}
	if (ray.side == 0)
		perp_wall_dist = (side_dist.x - delta_dist.x);
	else
		perp_wall_dist = (side_dist.y - delta_dist.y);

	ray.wall_dist = perp_wall_dist;
	ray.tile = map[vec_map.y][vec_map.x];
	ray.intersection.x = (pos.x + (ray.dir.x * perp_wall_dist));
	ray.intersection.y = (pos.y + (ray.dir.y * perp_wall_dist));

	return (ray);
}

void	cast_rays(char **map, t_render *render, t_player *p)
{
	int		x;
	double	camera_x;
	t_vec2d	dir;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = (double)(2.0 * x / WIDTH) - 1;
		dir = vec_assign(p->dir.x + (p->plane.x * camera_x), p->dir.y + (p->plane.y * camera_x));
		render->rays[x] = raycast(map, p->pos, dir);
		x++;
	}
}
