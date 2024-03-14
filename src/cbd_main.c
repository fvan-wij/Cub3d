#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_render.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cbd_audio.h>

bool	cbd_main(t_app *cbd)
{
	if (cbd_init(cbd))
		return (FAILURE);

	cbd->audio = cbd_init_audio();
	play_sound(cbd->audio, SND_MUSIC);

	mlx_loop(cbd->mlx);
	mlx_terminate(cbd->mlx);
	cleanup(cbd);

	cbd_uninit_audio(cbd->audio);
	cleanup(cbd);
	return (SUCCESS);
}
