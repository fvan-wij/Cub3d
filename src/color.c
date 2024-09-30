#include <cub3d.h>
#include <math.h>

t_rgba	color_darken(t_rgba color, int amount)
{
	t_rgba	new_color;

	if (color.r - amount < 0)
		new_color.r = 0;
	else
		new_color.r = color.r - amount;
	if (color.g - amount < 0)
		new_color.g = 0;
	else
		new_color.g = color.g - amount;
	if (color.b - amount < 0)
		new_color.b = 0;
	else
		new_color.b = color.b - amount;
	new_color.a = color.a;
	return (new_color);
}

t_rgba	get_color_from_tex(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	t_rgba	color;
	uint8_t	*dst;

	if (x >= tex->width || y >= tex->height)
	{
		color.r = 0;
		color.g = 0;
		color.b = 0;
		color.a = 0;
		return (color);
	}
	dst = tex->pixels + (y * tex->width + x) * 4;
	color.r = dst[0];
	color.g = dst[1];
	color.b = dst[2];
	color.a = dst[3];
	return (color);
}

t_rgba	color32(uint32_t color)
{
	t_rgba rgba;

	rgba.color = color;
	return (rgba);
}

int32_t	color(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return (color.color);
}

int32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color.color);
}
