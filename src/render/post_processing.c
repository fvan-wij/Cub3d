#include <cub3d.h>
#include <math.h>

void	draw_gradient_bg(t_hud *hud)
{
    double distance;
	uint32_t width = hud->img[HUD_OVERLAY]->width;
	uint32_t height = hud->img[HUD_OVERLAY]->height;
    double max_dist = sqrt(pow(width / 2, 2) + pow(height / 2, 2));
    t_rgba current_col;
	float centerX = width /2;
	float centerY = height /2;
	t_rgba color1;
	t_rgba color2;
	color1.color = color(151, 0, 0);
	color2.color = color(0, 0, 0);

    for (uint32_t x = 0; x < width; ++x) {
        for (uint32_t y = 0; y < height; ++y) {
            distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
            if (distance <= max_dist) {
                double ratio = distance / max_dist;
                current_col.r = color1.r + ratio * (color2.r - color1.r);
                current_col.g = color1.g + ratio * (color2.g - color1.g);
                current_col.b = color1.b + ratio * (color2.b - color1.b);
                current_col.a = 75;
				if (x < width && y < height)
                	mlx_put_pixel(hud->img[HUD_OVERLAY], x, y, current_col.color);
            }
        }
    }
}

