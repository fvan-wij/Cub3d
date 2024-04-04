#include <cub3d.h>
#include <stdio.h>

// static void	strip_1(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 1)
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_2(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 2)
// 		draw_wall_strip(render, x, walls->w_tex[1], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_3(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 3)
// 		draw_wall_strip(render, x, walls->w_tex[2], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_4(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 4)
// 		draw_wall_strip(render, x, walls->w_tex[3], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_5(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 5)
// 		draw_wall_strip(render, x, walls->w_tex[4], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_6(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 6)
// 		draw_wall_strip(render, x, walls->w_tex[5], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_7(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 7)
// 		draw_wall_strip(render, x, walls->w_tex[6], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_8(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 8)
// 		draw_wall_strip(render, x, walls->w_tex[7], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_9(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_w >= 9)
// 		draw_wall_strip(render, x, walls->w_tex[8], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_c1(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_cw >= 1)
// 		draw_wall_strip(render, x, walls->cw_tex[0], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_c2(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_cw >= 2)
// 		draw_wall_strip(render, x, walls->cw_tex[1], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }

// static void	strip_c3(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	if (walls->n_cw >= 3)
// 		draw_wall_strip(render, x, walls->cw_tex[2], wall_dist);
// 	else
// 		draw_wall_strip(render, x, walls->w_tex[0], wall_dist);

// }

// static void	strip_default(t_render render, int x, t_wall *walls, float wall_dist)
// {
// 	draw_wall_strip(render, x, walls->w_tex[0], wall_dist);
// }


// /*
// ** Initialized assigns wall_strip_functions to mapcharacters
// **
// */
// void	initialize_jump_table(wall_strip_func jump_table[256])
// {
// 	size_t	i;
// 	i = 0;
// 	while (i < 256)
// 	{
// 		jump_table[i] = strip_default;
// 		i++;
// 	}
// 	jump_table['1'] = strip_1;
// 	jump_table['2'] = strip_2;
// 	jump_table['3'] = strip_3;
// 	jump_table['4'] = strip_4;
// 	jump_table['5'] = strip_5;
// 	jump_table['6'] = strip_6;
// 	jump_table['7'] = strip_7;
// 	jump_table['8'] = strip_8;
// 	jump_table['9'] = strip_9;
// 	jump_table['='] = strip_c1;
// 	jump_table['-'] = strip_c2;
// 	jump_table['_'] = strip_c3;
// }

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
		// printf("");
		draw_wall_strip(render, x, map->walls.w_tex[(unsigned char)render.rays[x].tile], render.rays[x].wall_dist * 30);
		// map->walls.jump_table[(unsigned char)render.rays[x].tile](render, x, &map->walls, render.rays[x].wall_dist * 30);
		x++;
	}
}
