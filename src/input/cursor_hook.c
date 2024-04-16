#include <cub3d.h>

void	cursor_hook(double xpos, double ypos, void* param)
{
	t_app *cbd;

	cbd = (t_app*)param;
	if (cbd->state == STATE_GAME)
	{
		cbd->mouse.x = xpos;
		cbd->mouse.y = ypos;
	}
}