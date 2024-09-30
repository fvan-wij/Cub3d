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
static bool initialized = false;

bool	cbd_main(t_app *cbd, bool initialized)
{
	if (!initialized)
	{
		cbd_init(cbd);
		cbd->audio = cbd_init_audio();
		play_sound(cbd->audio, SND_MENU, 0.6f, 1.0f);
	}
	mlx_loop(cbd->mlx);
	return true;
	// mlx_terminate(cbd->mlx);
	// cbd_uninit_audio(cbd->audio);
	// cleanup(cbd);
}

void	emscripten_main_loop()
{
	if (!initialized)
	{
		t_app cbd;

		ft_memset(&cbd, 0, sizeof(t_app));
		cbd.mapdata = cbd_parse_map("./data/maps/dark_secret.cub");
		if (!cbd.mapdata)
		{
			fprintf(stderr, "Error parsing map");
		}
		else
			initialized = cbd_main(&cbd, initialized);
	}
}

int32_t	main(void)
{
	emscripten_set_main_loop(emscripten_main_loop, 0, true);
	return (SUCCESS);
}
