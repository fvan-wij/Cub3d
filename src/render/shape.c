#include <MLX42.h>
#include <cub3d.h>
#include <math.h>

void	draw_square(mlx_image_t *image, uint32_t color, t_vec pos, t_vec dimension)
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

void	draw_circle(mlx_image_t *image, uint32_t color, t_vec pos, float r)
{
	int 		angle;
	int 		inner;
	t_vec 		loc;

	angle = 0;
	while (angle < 360)
	{
		inner = 0;
		while (inner < r)
		{
			loc.x = inner * cos(angle) + pos.x;
			loc.y = inner * sin(angle) + pos.y;
			mlx_put_pixel(image, loc.x, loc.y, color);
			inner++;
		}
		angle++;
	}
}
