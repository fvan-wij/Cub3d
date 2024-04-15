#include <cub3d.h>

/*
 Function that checks the mouse and cursor input and updates
 the game accordingly
 cursor input is used to move the player's view and is already received
 inside the cursor_hook function
*/
void	mouse_input(t_app *cbd)
{
	double	delta_time;
	double	delta_x;
	double	delta_y;

	delta_time = cbd->mlx->delta_time;
	delta_x = cbd->mouse.x - cbd->prev_mouse.x;
	delta_y = cbd->mouse.y - cbd->prev_mouse.y;
	cbd->prev_mouse = cbd->mouse;

	// cbd->mouse.x = cbd->mouse.x - cbd->mlx->width / 2;
	// cbd->mouse.y = cbd->mouse.y - cbd->mlx->height / 2;
	// mlx_set_mouse_pos(cbd->mlx, 0, 0);

	// printf("Mouse x: %f\n", cbd->mouse.x);

	cbd->playerdata.dir = vec_rotate(cbd->playerdata.dir, delta_x * 0.05 * delta_time);
	cbd->playerdata.plane = vec_rotate(cbd->playerdata.plane, delta_x * 0.05 * delta_time);

	cbd->playerdata.head_height -= delta_y * 20 * delta_time;
	if (cbd->playerdata.head_height > 200)
		cbd->playerdata.head_height = 200;
	else if (cbd->playerdata.head_height < -200)
		cbd->playerdata.head_height = -200;
	cbd->render.y_offset += cbd->playerdata.head_height;
	printf("Head height: %f\n", cbd->playerdata.head_height);
}