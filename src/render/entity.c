#include <cub3d.h>
#include <stdlib.h>
#include <stdio.h>

t_rgba	get_animated_pixel(t_animation ani, mlx_texture_t *tex, int texX, int texY)
{
	t_rgba	color;
	int		frameX;
	int		frameY;
	int		frame_width;
	int		frame_height;

	frame_width = tex->width / ani.n_frames;
	frameX = texX + frame_width * ani.current_frame;
	frameY = texY + frame_width * ani.current_animation;
	color = get_color_from_tex(tex, frameX, frameY);
	return (color);
}

void	render_entities(t_render *render, t_entity *entities, t_player *player)
{
	t_entity	*ent;
	double	entity_distance;
	int		entity_zbuffer[WIDTH];

	ent = entities;
	ft_memset(render->sprite_img->pixels, 0, WIDTH * HEIGHT * 4);
	// ft_memset(entity_zbuffer, INT32_MAX, WIDTH * sizeof(int));
	//ENTITY CASTING
	//Start drawing entities
	while (ent)
	{
		entity_distance = ((player->pos.x - ent->pos.x) * (player->pos.x - ent->pos.x) + (player->pos.y - ent->pos.y) * (player->pos.y - ent->pos.y));

		//translate entity position to relative to camera
		double ent_x = ent->pos.x - player->pos.x;
		double ent_y = ent->pos.y - player->pos.y;

		//transform sprite with the inverse camera matrix
		// [ player->plane.x   player->dir.y ] -1                                       [ dirY      -dirX ]
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
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
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
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y - vMoveScreen) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				t_rgba color = get_animated_pixel(ent->animation, ent->texture, texX, texY); //get current color from the texture
				color = color_darken(color, transformY * 30); //make the color darker if it's further away
				if (y + render->y_offset >= 0 && y + render->y_offset < HEIGHT)
				{
					mlx_put_pixel(render->sprite_img, stripe, y + render->y_offset, color.color); //paint pixel if it isn't black, black is the invisible color
					entity_zbuffer[stripe] = entity_distance;

				}
			}
		}
		ent = ent->next;
	}
}