#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <math.h>

t_vec2d	move_forward(t_app *cbd, float speed, char **map)
{
	t_vec2d potential_pos;

	potential_pos.x = cbd->playerdata.pos.x + cbd->playerdata.dir.x * speed;
	potential_pos.y = cbd->playerdata.pos.y + cbd->playerdata.dir.y * speed;
	potential_pos = resolve_collision(map, cbd->playerdata.pos, cbd->playerdata.dir, potential_pos);
	resolve_particles(cbd->particles, -3);
	headbob(&cbd->render.headbob, speed * 7);
	return (potential_pos);
}

t_vec2d	move_backwards(t_app *cbd, float speed, char **map)
{
	t_vec2d potential_pos;

	potential_pos.x = cbd->playerdata.pos.x - cbd->playerdata.dir.x * speed;
	potential_pos.y = cbd->playerdata.pos.y - cbd->playerdata.dir.y * speed;
	potential_pos = resolve_collision(map, cbd->playerdata.pos, cbd->playerdata.dir, potential_pos);
	resolve_particles(cbd->particles, 3);
	headbob(&cbd->render.headbob, speed * 7);
	return (potential_pos);
}

void	rotate_player(t_player *playerdata, t_particle *particles, float angle)
{
	rotate_particles(particles, -angle * 160);
	playerdata->dir = vec_rotate(playerdata->dir, angle);
	playerdata->plane = vec_rotate(playerdata->plane, angle);
}

t_vec2d strafe_player(t_app *cbd, float speed, int8_t direction)
{
	t_vec2d	potential_pos;
	t_vec2d dir;

	if (direction == -1)
	{
		dir = vec_rotate(cbd->playerdata.dir, -M_PI_2);
		resolve_particles(cbd->particles, -3);
	}
	else
	{
		dir = vec_rotate(cbd->playerdata.dir, M_PI_2);
		resolve_particles(cbd->particles, 3);
	}
	potential_pos.x = cbd->playerdata.pos.x + dir.x * speed;
	potential_pos.y = cbd->playerdata.pos.y + dir.y * speed;
	potential_pos = resolve_collision(cbd->mapdata->cbd_map, cbd->playerdata.pos, cbd->playerdata.dir, potential_pos);
	return (potential_pos);
}

void	move_player(t_app *cbd)
{
	t_vec2d	potential_pos;
	float 	move_speed;

	move_speed = cbd->mlx->delta_time * 1.15;
	potential_pos = cbd->playerdata.pos;

	//Shift multiplier
	if (cbd->playerdata.state == PLAYER_RUNNING)
		move_speed *= 1.45;

	//Player movement input polling
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP) || mlx_is_key_down(cbd->mlx, MLX_KEY_W))
		potential_pos = move_forward(cbd, move_speed, cbd->mapdata->cbd_map);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN) || mlx_is_key_down(cbd->mlx, MLX_KEY_S))
		potential_pos = move_backwards(cbd, move_speed, cbd->mapdata->cbd_map);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_A))
		potential_pos = strafe_player(cbd, move_speed, -1);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_D))
		potential_pos = strafe_player(cbd, move_speed, 1);
	else
		reset_player_animation(&cbd->render, cbd->mlx);

	//Player rotation
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= cbd->mapdata->width)
		rotate_player(&cbd->playerdata, cbd->particles, cbd->mlx->delta_time * 1.5);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
		rotate_player(&cbd->playerdata, cbd->particles, -cbd->mlx->delta_time * 1.5);

	//Resolve movement
	peek_map(cbd->playerdata.inv, &cbd->render, cbd->render.hud->img[HUD_MAP], cbd->mlx);
	cbd->playerdata.pos = potential_pos;
	cbd->render.y_offset += (sin(cbd->render.headbob) * 10) + cbd->render.map_peak;
}
