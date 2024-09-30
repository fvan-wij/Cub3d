#include <MLX42.h>
#include <cub3d.h>
#include <stdlib.h>
#include <stdio.h>

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
		if ((bh.cx >= 0 && bh.cx < WIDTH) && (bh.cy >= 0 && bh.cy < HEIGHT))
			mlx_put_pixel(image, bh.cx, bh.cy, color);
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

static bool	is_vertical(t_vec2i p1, t_vec2i p2)
{
	return (p1.x == p2.x);
}

static void	draw_vert_line(mlx_image_t *image, uint32_t color, t_vec2i p1, t_vec2i p2)
{
	int dir;
	int y;

	if (p1.y < p2.y)
		dir = 1;
	else
		dir = -1;
	y = p1.y;
	while (y != p2.y)
	{
		if ((p1.x >= 0 && p1.x < WIDTH) && (y >= 0 && y < HEIGHT))
		{
			mlx_put_pixel(image, p1.x, y, color);
		}
		y += dir;
	}
}

void	draw_line(mlx_image_t *image,
	uint32_t color, t_vec2i p1, t_vec2i p2)
{
	t_bresenham 	bh;
	t_line 			l;

	if (is_vertical(p1, p2))
		return (draw_vert_line(image, color, p1, p2));
	l.x1 = p1.x;
	l.y1 = p1.y;
	l.x2 = p2.x;
	l.y2 = p2.y;
	ft_bzero(&bh, sizeof(t_bresenham));
	bh.sx = sign_x(p1.x, p2.x);
	bh.sy = sign_y(p1.y, p2.y);
	bh.dx = abs(p2.x - p1.x);
	bh.dy = abs(p2.y - p1.y);
	bh.error[0] = bh.dx - bh.dy;
	bh.cx = p1.x;
	bh.cy = p1.y;
	draw_bresenham_line(image, color, bh, l);
}
