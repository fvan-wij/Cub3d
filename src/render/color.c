#include <cub3d.h>
#include <math.h>

int32_t	color(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return (color.color);
}
