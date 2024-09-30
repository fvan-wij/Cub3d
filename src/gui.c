#include <cub3d.h>

void	draw_healthbar(mlx_image_t *img, t_vec2i pos, int health)
{
	//img col pos dim
	t_rgba col = {0xEE0000FF};
	int hp_modifier = 200 / 5;
	t_vec2i size = {health * hp_modifier, 20};
	draw_square(img, col.color, pos, size);
}

void	draw_fuelbar(mlx_image_t *img, t_vec2i pos, int fuel)
{
	//img col pos dim
	t_rgba col = {0x30010FF};
	if (fuel > 200)
		fuel = 200;
	t_vec2i size = {fuel, 20};
	draw_square(img, col.color, pos, size);
}
