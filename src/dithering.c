#include <cbd_render.h>
#include <math.h>

static uint32_t	index_at(uint32_t x, uint32_t y, uint32_t width, uint8_t bpp)
{
	int index = (x + y * width) * bpp; //Looping over every pixel;
	return (index);
}

mlx_texture_t	*dither_texture(mlx_texture_t *tex)
{
	uint32_t x;
	uint32_t y;

	y = 1;
	while (y < tex->height - 1)
	{
		x = 1;
		while (x < tex->width - 1)
		{
			int index = (x + y * tex->width) * tex->bytes_per_pixel; //Looping over every pixel;
			uint8_t r = tex->pixels[index];
			uint8_t g = tex->pixels[index + 1];
			uint8_t b = tex->pixels[index + 2];

			// Convert to grayscales
			// uint32_t total = (r + g + b)/3 * 255;
			// tex->pixels[index] = total;
			// tex->pixels[index + 1] = total;
			// tex->pixels[index + 2] = total;

			int factor = 3;

			uint8_t new_r = round(((factor * r>>8)) * ((255>>1)));
			uint8_t new_g = round(((factor * g>>8)) * ((255>>1)));
			uint8_t new_b = round(((factor * b>>8)) * ((255>>1)));

			int32_t q_r = r - new_r;
			int32_t q_g = g - new_g;
			int32_t q_b = b - new_b;

			tex->pixels[index	 ]	= new_r;
			tex->pixels[index + 1]	= new_g;
			tex->pixels[index + 2] 	= new_b;

			//Red
			tex->pixels[index_at(x + 1, y    , tex->width, tex->bytes_per_pixel)] = tex->pixels[index_at(x + 1, y, tex->width, tex->bytes_per_pixel)] 				+ q_r * 7 / 16;
			tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel)] = tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel)] 			+ q_r * 3 / 16;
			tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel)] = tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel)] 			+ q_r * 5 / 16;

			//Red
			tex->pixels[index_at(x + 1, y    , tex->width, tex->bytes_per_pixel) + 1] = tex->pixels[index_at(x + 1, y, tex->width, tex->bytes_per_pixel) + 1] 		+ q_g * 7 / 16;
			tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel) + 1] = tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel) + 1] 	+ q_g * 3 / 16;
			tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel) + 1] = tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel) + 1] 	+ q_g * 5 / 16;

			//Blue
			tex->pixels[index_at(x + 1, y    , tex->width, tex->bytes_per_pixel) + 2] = tex->pixels[index_at(x + 1, y, tex->width, tex->bytes_per_pixel) + 2] 		+ q_b * 7 / 16;
			tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel) + 2] = tex->pixels[index_at(x - 1, y + 1, tex->width, tex->bytes_per_pixel) + 2] 	+ q_b * 3 / 16;
			tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel) + 2] = tex->pixels[index_at(x    , y + 1, tex->width, tex->bytes_per_pixel) + 2] 	+ q_b * 5 / 16;
			x++;
		}
		y++;
	}
	return (tex);
}

mlx_image_t	*dither_image(mlx_image_t *img)
{
	uint32_t x;
	uint32_t y;

	y = 1;
	while (y < img->height - 1)
	{
		x = 1;
		while (x < img->width - 1)
		{
			int index = (x + y * img->width) * 4;
			uint8_t r = img->pixels[index];
			uint8_t g = img->pixels[index + 1];
			uint8_t b = img->pixels[index + 2];

			int factor = 2;

			uint8_t new_r = round(((factor * r>>8)) * ((255>>1)));
			uint8_t new_g = round(((factor * g>>8)) * ((255>>1)));
			uint8_t new_b = round(((factor * b>>8)) * ((255>>1)));

			int32_t q_r = r - new_r;
			int32_t q_g = g - new_g;
			int32_t q_b = b - new_b;

			img->pixels[index	 ]	= new_r;
			img->pixels[index + 1]	= new_g;
			img->pixels[index + 2] 	= new_b;


			img->pixels[index_at(x + 1, y    , img->width, 4)] = img->pixels[index_at(x + 1, y, img->width, 4)] 				+ q_r * 7 / 16;
			img->pixels[index_at(x - 1, y + 1, img->width, 4)] = img->pixels[index_at(x - 1, y + 1, img->width, 4)] 			+ q_r * 3 / 16;
			img->pixels[index_at(x    , y + 1, img->width, 4)] = img->pixels[index_at(x    , y + 1, img->width, 4)] 			+ q_r * 5 / 16;

			img->pixels[index_at(x + 1, y    , img->width, 4) + 1] = img->pixels[index_at(x + 1, y, img->width, 4) + 1] 		+ q_g * 7 / 16;
			img->pixels[index_at(x - 1, y + 1, img->width, 4) + 1] = img->pixels[index_at(x - 1, y + 1, img->width, 4) + 1] 	+ q_g * 3 / 16;
			img->pixels[index_at(x    , y + 1, img->width, 4) + 1] = img->pixels[index_at(x    , y + 1, img->width, 4) + 1] 	+ q_g * 5 / 16;

			img->pixels[index_at(x + 1, y    , img->width, 4) + 2] = img->pixels[index_at(x + 1, y, img->width, 4) + 2] 		+ q_b * 7 / 16;
			img->pixels[index_at(x - 1, y + 1, img->width, 4) + 2] = img->pixels[index_at(x - 1, y + 1, img->width, 4) + 2] 	+ q_b * 3 / 16;
			img->pixels[index_at(x    , y + 1, img->width, 4) + 2] = img->pixels[index_at(x    , y + 1, img->width, 4) + 2] 	+ q_b * 5 / 16;
			x++;
		}
		y++;
	}
	return (img);
}

