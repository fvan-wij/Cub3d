#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <stdio.h>
#include <MLX42.h>
#include <stdlib.h>

#define WHITE 0xFFFFFFFF

void	draw_grid(t_app *cbd, int width, int height)
{
	t_vec p1;	
	t_vec p2;
	int	i;
	int	j;
	int tilesize = WIDTH / width;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			p1.x = j;
			p1.y = i;
			p2.x = j + tilesize;
			p2.y = i + tilesize;
			draw_line(cbd->game, WHITE, p1, p2);
			j++;
		}
		i++;
	}

}

int32_t	main(int argc, char *argv[])
{
	t_app cbd;

	ft_memset(&cbd, 0, sizeof(t_app));
	if (!arg_is_valid(argc, argv))
		return (FAILURE);
	cbd.mapdata = cbd_parse_map(argv[1], &cbd);
	if (!cbd.mapdata)
		return (FAILURE);
	print_debug_info(&cbd);

	//MLX
	cbd.mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd.mlx)
		return (FAILURE);

	//Main loop
	cbd.menudata = cbd_init_menu(cbd.mlx);
	if (!cbd.menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);
	//Draw 2D representation of the map;

	// t_vec p1 = {0, HEIGHT/2};
	// t_vec p2 = {WIDTH, HEIGHT/2};

	// cbd.game = mlx_new_image(cbd.mlx, WIDTH, HEIGHT);
	// draw_line(cbd.game, 0xFFFFFFFF, p1, p2);
	// draw_grid(&cbd, cbd.mapdata->width, cbd.mapdata->height);
	// mlx_image_to_window(cbd.mlx, cbd.game, 0, 0);
	

	mlx_key_hook(cbd.mlx, navigate_menu, &cbd);
	mlx_loop(cbd.mlx);
	mlx_terminate(cbd.mlx);
	return (SUCCESS);
}
