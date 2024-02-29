#include <MLX42.h>
#include <cub3d.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	draw_square(mlx_image_t *image, uint32_t color, t_vec_f pos, t_vec dimension)
{
	int reset;

	dimension.x += pos.x;
	dimension.y += pos.y;

	reset = pos.x;
	while (pos.y < dimension.y)
	{
		pos.x = reset;
		while (pos.x < dimension.x)
		{
			mlx_put_pixel(image, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
