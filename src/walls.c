#include <cub3d.h>
#include <stdio.h>

/*
** Draws the walls (bonus) using char-based jump_table
** 	Needs:
** 		The game image
** 		The raycasting data
** 		The headbobbing data
** 		The map peak data
**		The wall texture data
*/
void	draw_walls_bonus(t_render render, t_map *map)
{
	int 	x;

	x = 0;
	while (x < WIDTH)
	{
		draw_wall_strip(render, x, map->walls.w_tex[(unsigned char)render.rays[x].tile], render.rays[x].wall_dist * 30);
		x++;
	}
}
