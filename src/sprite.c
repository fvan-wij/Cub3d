#include <cub3d.h>
#include <stdlib.h>

#define numSprites 1

void	draw_sprites(t_render *render, t_map *map, t_player *player)
{
	t_sprite	*sprite;
	double		spriteDistance[numSprites];
	int			spriteOrder[numSprites];
	(void) 		map;

	ft_memset(render->sprite_img->pixels, 0, WIDTH * HEIGHT * 4);
	sprite = render->sprite;
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < numSprites; i++)
	{
	  spriteOrder[i] = i;
	  spriteDistance[i] = ((player->pos.x - sprite[i].pos.x) * (player->pos.x - sprite[i].pos.x) + (player->pos.y - sprite[i].pos.y) * (player->pos.y - sprite[i].pos.y));//sqrt not taken, unneeded
	}
	// sortSprites(spriteOrder, spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < numSprites; i++)
	{
	  //translate sprite position to relative to camera
	  double spriteX = sprite[spriteOrder[i]].pos.x - player->pos.x;
	  double spriteY = sprite[spriteOrder[i]].pos.y - player->pos.y;
	  t_sprite cur_sprite = sprite[spriteOrder[i]];

	  //transform sprite with the inverse camera matrix
	  // [ player->plane.x   player->dir.y ] -1                                       [ dirY      -dirX ]
	  // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	  // [ planeY   dirY ]                                          [ -planeY  planeX ]

	  double invDet = 1.0 / (player->plane.x * player->dir.y - player->dir.x * player->plane.y); //required for correct matrix multiplication

	  double transformX = invDet * (player->dir.y * spriteX - player->dir.x * spriteY);
	  double transformY = invDet * (-player->plane.y * spriteX + player->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

	  int spriteScreenX = (int)((WIDTH / 2) * (1.0 + transformX / transformY));

	  //calculate height of the sprite on screen
	  int spriteHeight = abs((int)(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	  //calculate lowest and highest pixel to fill in current stripe
	  int drawStartY = (-spriteHeight / 2) + (HEIGHT / 2) + render->y_offset;
	  if(drawStartY < 0) drawStartY = 0;
	  int drawEndY = (spriteHeight / 2) + (HEIGHT / 2) + render->y_offset;
	  if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

	  //calculate width of the sprite
	  int spriteWidth = abs((int)(HEIGHT / (transformY)));
	  int drawStartX = -spriteWidth / 2 + spriteScreenX;
	  if(drawStartX < 0) drawStartX = 0;
	  int drawEndX = spriteWidth / 2 + spriteScreenX;
	  if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;


	int texWidth = cur_sprite.tex->width;
	int texHeight = cur_sprite.tex->height;
	  //loop through every vertical stripe of the sprite on screen
	  for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	  {
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < render->rays[stripe].wall_dist)
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				t_rgba color = get_color_from_tex(cur_sprite.tex, texX, texY); //get current color from the texture
				color = color_darken(color, transformY * 30); //make the color darker if it's further away
				if (y + render->y_offset >= 0 && y + render->y_offset < HEIGHT)
					mlx_put_pixel(render->sprite_img, stripe, y + render->y_offset, color.color); //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}
