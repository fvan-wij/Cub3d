#include <cub3d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	draw_scanlines_bg(mlx_image_t *img)
{
	t_rgba		c;
	uint32_t 	y;
	uint32_t 	x;

	y = 0;
	while (y < img->height)
	{
		if (y % 5 == 0)
		{
			x = 0;
			while (x < img->width)
			{
				uint8_t	v1 = rand();
				c.r = v1;
				c.g = v1;
				c.b = v1;
				c.a = 80;
				if (x < img->width && y < img->height)
						mlx_put_pixel(img, x, y, c.color);
				x++;
			}
		}
		y++;
	}
}

void	draw_radial_overlay(mlx_image_t *img, t_app *cbd)
{
	double distance;
	t_rgba current_col;
	t_rgba color1;
	t_rgba color2;
	uint32_t y;
	uint32_t x;

	const uint32_t width = img->width;
	const uint32_t height =img->height;
	const double max_dist = sqrt(pow((float)width / 2, 2) + pow((float)height / 2, 2));
	const float centerX = width>>1;
	const float centerY = height>>1;
	double col2_mult = 0;

	color1.color = color_rgba(0, 0, 0, 0);
	color2.color = color_rgba(0, 0, 0, 0);
	if (cbd->playerdata.health == 2)
	{
		color2.color = color_rgba(0, 0, 0, 0);
	}
	else if (cbd->playerdata.health == 1)
	{
		col2_mult = sin(cbd->render.headache_timer) + 2;
		color2.color = color_rgba(fabs(col2_mult) * 40, 0, 0, 100);
	}

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
			if (distance <= max_dist)
			{
				double ratio = distance / max_dist;
				current_col.r = color1.r + ratio * (color2.r - color1.r);
				current_col.g = color1.g + ratio * (color2.g - color1.g);
				current_col.b = color1.b + ratio * (color2.b - color1.b);
				current_col.a = color1.a + ratio * (color2.a - color1.a);
				if (x < width && y < height)
					mlx_put_pixel(img, x, y, current_col.color);
			}
			x++;
		}
		y++;
	}
	// draw_scanlines_bg(img);
}

void	draw_gradient_top(mlx_image_t *img, int32_t top, int32_t bot, int32_t end)
{
	t_rgba c1;
	t_rgba c2;
	c1.color = top;
	c2.color = bot;
	uint32_t	cap;
	cap = (img->height>>1) + end;
	const float step_r = (float)(c2.r - c1.r) / cap;
	const float step_g = (float)(c2.g - c1.g) / cap;
	const float step_b = (float)(c2.b - c1.b) / cap;
	const float step_a = (float)(c2.a - c1.a) / cap;
	t_rgba 		color;
	uint32_t 	y;
	uint32_t 	x;

	y = 0;
	while (y < cap)
	{
		x = 0;
		while (x < img->width)
		{
			color.r = c1.r + step_r * y;
			color.g = c1.g + step_g * y;
			color.b = c1.b + step_b * y;
			color.a = c1.a + step_a * y;
			if (x < img->width && y < img->height)
				mlx_put_pixel(img, x, y, color.color);
			x++;
		}
		y++;
	}
}

void	draw_gradient_bot(mlx_image_t *img, int32_t top, int32_t bot, int32_t end)
{
	t_rgba c1;
	t_rgba c2;
	c1.color = top;
	c2.color = bot;
	uint32_t	cap;
	cap = (img->height>>1) + end;
	const float step_r = (float)(c2.r - c1.r) / cap;
	const float step_g = (float)(c2.g - c1.g) / cap;
	const float step_b = (float)(c2.b - c1.b) / cap;
	const float step_a = (float)(c2.a - c1.a) / cap;
	t_rgba 		color;
	uint32_t 	y;
	uint32_t 	x;

	y = cap;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color.r = c1.r + step_r * (y - cap);
			color.g = c1.g + step_g * (y - cap);
			color.b = c1.b + step_b * (y - cap);
			color.a = c1.a + step_a * (y - cap);
			if (x < img->width && y < img->height)
				mlx_put_pixel(img, x, y, color.color);
			x++;
		}
		y++;
	}
}

void draw_gradient_bg(mlx_image_t *img, int32_t c1, int32_t c2, int32_t offset)
{
	draw_gradient_top(img, c1, c2, offset);
	draw_gradient_bot(img, c2, c1, offset);
}

void	screenshake(t_render *render)
{
	if (render->fx.crt)
	{
		render->headbob += 10;
		draw_scanlines_bg(render->img);
	}
}
