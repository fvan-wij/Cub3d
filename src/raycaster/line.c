#include <MLX42.h>
#include <cub3d.h>
#include <math.h>
#include <stdlib.h>


void	draw_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
		mlx_put_pixel(image, x, y, color);
}

static int	sign_x(int x1, int x2)
{
	if (x1 < x2)
		return (1);
	return (-1);
}

static int	sign_y(int y1, int y2)
{
	if (y1 < y2)
		return (1);
	return (-1);
}

static void	draw_bresenham_line(mlx_image_t *image,
	uint32_t color, t_bresenham bh, t_line l)
{
	while (bh.cx != l.x2 || bh.cy != l.y2)
	{
		draw_pixel(image, bh.cx, bh.cy, color);
		bh.error[1] = bh.error[0] * 2;
		if (bh.error[1] > (-bh.dy))
		{
			bh.error[0] -= bh.dy;
			bh.cx += bh.sx;
		}
		if (bh.error[1] < bh.dx)
		{
			bh.error[0] += bh.dx;
			bh.cy += bh.sy;
		}
	}
}

void	draw_line(mlx_image_t *image,
	uint32_t color, t_vec p1, t_vec p2)
{
	t_bresenham 	bh;
	t_line 			l;

	l.x1 = p1.x;
	l.y1 = p1.y;
	l.x2 = p2.x;
	l.y2 = p1.y;
	ft_bzero(&bh, sizeof(t_line));
	bh.sx = sign_x(p1.x, p2.x);
	bh.sy = sign_y(p1.y, p2.y);
	bh.dx = abs(p2.x - p1.x);
	bh.dy = abs(p2.y - p1.y);
	bh.error[0] = bh.dx - bh.dy;
	bh.cx = p1.x;
	bh.cy = p1.y;
	draw_bresenham_line(image, color, bh, l);
}
