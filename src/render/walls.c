#include <cub3d.h>
#include <stdio.h>

static void	strip_1(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (1 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_2(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (2 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[1], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_3(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (3 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[2], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_4(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (4 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[3], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_5(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (5 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[4], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_6(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (6 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[5], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_7(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (7 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[6], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_8(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (8 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[7], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_9(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (9 < walls->n_w)
		draw_wall_strip(render, x, walls->w_tex[8], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_c1(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (1 <= walls->n_cw)
		draw_wall_strip(render, x, walls->cw_tex[0], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_c2(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (2 <= walls->n_cw)
		draw_wall_strip(render, x, walls->cw_tex[1], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}

static void	strip_c3(t_render render, int x, t_wall *walls, float wall_dist)
{
	if (3 <= walls->n_cw)
		draw_wall_strip(render, x, walls->cw_tex[2], wall_dist);
	else
		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);

}

static void	strip_default(t_render render, int x, t_wall *walls, float wall_dist)
{
	draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
}


static void	initialize_pointer_array(wall_strip_func jump_table[256])
{
	size_t	i;
	i = 0;
	while (i < 256)
	{
		jump_table[i] = strip_default;
		i++;
	}
	jump_table['1'] = strip_1;
	jump_table['2'] = strip_2;
	jump_table['3'] = strip_3;
	jump_table['4'] = strip_4;
	jump_table['5'] = strip_5;
	jump_table['6'] = strip_6;
	jump_table['7'] = strip_7;
	jump_table['8'] = strip_8;
	jump_table['9'] = strip_9;
	jump_table['='] = strip_c1;
	jump_table['-'] = strip_c2;
	jump_table['_'] = strip_c3;

}

/*
** Draws the walls (bonus)
** 	Needs:
** 		The game image
** 		The raycasting data
** 		The headbobbing data
** 		The map peak data
**		The wall texture data
*/
void	draw_walls_bonus(t_render render, t_map *map)
{
	int 					x;
	wall_strip_func 	jump_table[256];

	initialize_pointer_array(jump_table);
	x = 0;
	while (x < WIDTH)
	{
		jump_table[(unsigned char)render.rays[x].tile](render, x, &map->walls, render.rays[x].wall_dist * 30);
		x++;
	}
}
