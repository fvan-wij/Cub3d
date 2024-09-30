#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>

#include <stdio.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <cbd_render.h>
#include <math.h>
#include <stdlib.h>
#include <cbd_audio.h>

static bool init = false;
static t_app cbd;

void	emscripten_main_loop()
{
	mlx_loop(cbd.mlx);
}

int32_t	main(void)
{
	if (!init)
	{
		ft_memset(&cbd, 0, sizeof(t_app));
		cbd.mapdata = cbd_parse_map("./data/maps/dark_secret.cub");
		if (!cbd.mapdata)
		{
			fprintf(stderr, "Error parsing map");
		}
		cbd_init(&cbd);
		cbd.audio = cbd_init_audio();
		play_sound(cbd.audio, SND_MENU, 0.6f, 1.0f);
		init = true;
	}
	emscripten_set_main_loop(emscripten_main_loop, 0, true);
	return (SUCCESS);
}
