#include <cub3d.h>
#include <stdlib.h>
#include <stdio.h>

t_rgba	color_depth(t_rgba color, double depth)
{
	t_rgba	new_color;
	double	depth_factor;

	if (depth > 10)
		depth = 10;
	depth_factor = depth / 10;
	depth_factor = 1 - depth_factor;
	new_color.r = 255 * depth_factor;
	new_color.g = 255 * depth_factor;
	new_color.b = 255 * depth_factor;
	new_color.a = color.a;
	return (new_color);
}

t_rgba	get_animated_pixel(t_animation ani, mlx_texture_t *tex, int texX, int texY)
{
	t_rgba	color;
	int		frameX;
	int		frameY;
	int		frame_width;
	// int		frame_height;

	frame_width = tex->width / ani.n_frames;
	frameX = texX + frame_width * ani.current_frame;
	frameY = texY + frame_width * ani.current_animation;
	color = get_color_from_tex(tex, frameX, frameY);
	return (color);
}

// t_rgba	transparent_color(t_rgba color1, t_rgba color2)
// {
// 	t_rgba	new_color;
// 	double	alpha;

// 	alpha = (double)color1.a / 255;
// 	new_color.r = (1 - alpha) * color2.r + alpha * color1.r;
// 	new_color.g = (1 - alpha) * color2.g + alpha * color1.g;
// 	new_color.b = (1 - alpha) * color2.b + alpha * color1.b;
// 	new_color.a = 255;
// 	return (new_color);
// }

// t_entity	**distance_sort_entities(t_entity *entities)
// {

// }

void	render_entities(t_render *render, t_entity *entities, t_player *player)
{
	t_entity	*ent;
	double	entity_zbuffer[WIDTH * HEIGHT];

	ent = entities;
	player->target_distance = 0;
	player->target_entity = NULL;
	ft_memset(render->sprite_img->pixels, 0, WIDTH * HEIGHT * 4);
	int i;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		entity_zbuffer[i] = 1000000;
		i++;
	}
	//ENTITY CASTING
	//Start drawing entities
	while (ent)
	{
		if (ent->enabled == false)
		{
			ent = ent->next;
			continue;
		}
		ent->distance = ((player->pos.x - ent->pos.x) * (player->pos.x - ent->pos.x) + (player->pos.y - ent->pos.y) * (player->pos.y - ent->pos.y));

		if (ent->distance < 100.0)
			ent->distance /= 100;
		// if (ft_strncmp("tv", ent->name, 2) == 0)
		// 	printf("entity_distance:%f\n", ent->distance);

		//translate entity position to relative to camera
		double ent_x = ent->pos.x - player->pos.x;
		double ent_y = ent->pos.y - player->pos.y;

		//transform sprite with the inverse camera matrix
		// [ player->plane.x   player->dir.y ] -1                     [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (player->plane.x * player->dir.y - player->dir.x * player->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (player->dir.y * ent_x - player->dir.x * ent_y);
		double transformY = invDet * (-player->plane.y * ent_x + player->plane.x * ent_y); //this is actually the depth inside the screen, that what Z is in 3D

		//parameters for scaling and moving the sprites
		float	uDiv = 1;
		float	vDiv = 1;
		float	vMove = 0.0;
		int vMoveScreen = (int)(vMove / transformY);

		int spriteScreenX = (int)((WIDTH / 2) * (1.0 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(HEIGHT / (transformY))) / vDiv; //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen + render->y_offset;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen + render->y_offset;
		if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(HEIGHT / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

		int texWidth = ent->frame_width;
		int texHeight = ent->frame_height;
		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			// if (ent->type == ENTITY_ENEMY)
			// {
			// 	// update_entity(ent, render->cbd);
			// 	printf("current_frame:%zu\n", ent->animation.current_frame);
			// }
			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < render->rays[stripe].wall_dist)
			{
				int y = drawStartY;
				while (y < drawEndY) //for every pixel of the current stripe
				{
					int d = (y - vMoveScreen - render->y_offset) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					if (y >= 0 && y < HEIGHT)
					{
						t_rgba color = get_animated_pixel(ent->animation, ent->texture, texX, texY); //get current color from the texture
						color = color_darken(color, transformY * 30); //make the color darker if it's further away
						// color = color_depth(color, transformY); //depth effect
						if (color.a != 0 && transformY < entity_zbuffer[stripe + ((y) * WIDTH)]) //apply zbuffer
						{
							if (stripe == WIDTH / 2 && y == HEIGHT / 2)
							{
								player->target_distance = transformY;
								player->target_entity = ent;
							}
							mlx_put_pixel(render->sprite_img, stripe, y, color.color); //paint pixel if the alpha isn't 0
							entity_zbuffer[stripe + ((y) * WIDTH)] = transformY;
						}
					}
					y++;
				}
			}
		}
		ent = ent->next;
	}
}
