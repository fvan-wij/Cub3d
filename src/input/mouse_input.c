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

	rotate_player(&cbd->playerdata, cbd->particles, delta_x * 0.05 * delta_time);

	cbd->playerdata.head_height -= delta_y * 20 * delta_time;
	if (cbd->playerdata.head_height > 200)
		cbd->playerdata.head_height = 200;
	else if (cbd->playerdata.head_height < -200)
		cbd->playerdata.head_height = -200;
	else
		move_particles(cbd->particles, 0, -(delta_y * 20 * delta_time));

	cbd->render.y_offset += cbd->playerdata.head_height;
}