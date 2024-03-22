#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void	rotate_particles(t_particle *particles, float dir)
{
	int i;

	i = 0;
	dir *=2;
	while (i < N_PARTICLES)
	{
		particles[i].p.x += dir;
		i++;
	}
}

void	destroy_wall(t_map *mapdata, t_player *player)
{
	char target = mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)];
	if (target == '=')
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '-';
	else if (target == '-')
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '_';
	else if (target == '_')
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '0';
}

void	resolve_particles(t_particle *particles)
{
	int i = 0;
	while (i < N_PARTICLES)
	{
		if (particles[i].p.x < (WIDTH>>1))
			particles[i].dir.x = -1.0;
		else
			particles[i].dir.x = 1.0;
		particles[i].size.x -= 0.05;
		particles[i].size.y -= 0.05;
		particles[i].p.y -= 3;
		particles[i].p.x += particles[i].dir.x * 5;
		if (particles[i].size.x < 0 || particles[i].size.y < 0)
		{
			particles[i].size = particles[i].reset;
			particles[i].p = vec_assign((float) rand() / (float)RAND_MAX * WIDTH, (float) rand() / (float)RAND_MAX * HEIGHT);
		}
		i++;
	}
}

t_vec2d	resolve_collision(char **map, t_vec2d pos, t_vec2d dir, t_vec2d potential_pos)
{
	t_vec2d local_pos;
	float r = vec_length(dir) / 8;
	float overlap;

	local_pos.x = pos.x - (int) pos.x;
	local_pos.y = pos.y - (int) pos.y;
	char U = map[(int)pos.y - 1][(int)pos.x];
	char R = map[(int)pos.y][(int)pos.x + 1];
	char D = map[(int)pos.y + 1][(int)pos.x];
	char L = map[(int)pos.y][(int)pos.x - 1];

	if (local_pos.x <= 0.5 && is_wall_bonus(L))
	{
		float dl = local_pos.x;
		if (dl <= r)
		{
			overlap = r - dl;
			potential_pos.x = potential_pos.x + overlap;
		}
	}
	if (local_pos.y >= 0.5 && is_wall_bonus(D))
	{
		float dd = 1 - local_pos.y;
		if (dd <= r)
		{
			overlap = r - dd;
			potential_pos.y = potential_pos.y - overlap;
		}
	}
	if (local_pos.y <= 0.5 && is_wall_bonus(U))
	{
		float du = local_pos.y;
		if (du <= r)
		{
			overlap = r - du;
			potential_pos.y = potential_pos.y + overlap;
		}
	}
	if (local_pos.x >= 0.5 && is_wall_bonus(R))
	{
		float dr = 1 - local_pos.x;
		if (dr <= r)
		{
			overlap = r - dr;
			potential_pos.x = potential_pos.x - overlap;
		}
	}
	return (potential_pos);
}

void	move_player(t_app *cbd)
{
	t_vec2d pos;
	t_vec2d dir;
	t_vec2d	potential_pos;
	float 	move_speed;
	float 	headbob_speed;

	move_speed = cbd->mlx->delta_time * 2;
	headbob_speed = cbd->mlx->delta_time * 10;
	potential_pos = cbd->playerdata.pos;
	pos = vec_assign(cbd->playerdata.pos.x, cbd->playerdata.pos.y);
	dir = vec_assign(cbd->playerdata.dir.x, cbd->playerdata.dir.y);

	//Peek animation
	cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].img->instances[0].x = (cos(cbd->render.headbob) * 2) + (WIDTH>>1) - (cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].img->width>>1);
	if (cbd->hud->img[HUD_MAP]->enabled && cbd->render.map_peak > -100)
		cbd->render.map_peak -= cos(cbd->mlx->delta_time) * 2;
	else if (cbd->render.map_peak < 0)
		cbd->render.map_peak += cos(cbd->mlx->delta_time) * 2;

	//Shift multiplier
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT_SHIFT))
	{
		move_speed *= 1.25;
		headbob_speed *= 2.25;
	}

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
		destroy_wall(cbd->mapdata, &cbd->playerdata);

	//Player movement
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))//Move forward, resolve particles and collision
	{
		resolve_particles(cbd->particles);
		potential_pos.x = pos.x + dir.x * move_speed;
		potential_pos.y = pos.y + dir.y * move_speed;
		cbd->render.headbob += headbob_speed;
		if (cbd->render.headbob > 2 * M_PI)
			cbd->render.headbob = 0;
		potential_pos = resolve_collision(cbd->mapdata->cbd_map, pos, dir, potential_pos);
	}
	else if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN)) //Move backwards and resolve collision
	{
		potential_pos.x = pos.x - dir.x * move_speed;
		potential_pos.y = pos.y - dir.y * move_speed;
		potential_pos = resolve_collision(cbd->mapdata->cbd_map, pos, dir, potential_pos);
		cbd->render.headbob += headbob_speed;
		if (cbd->render.headbob > 2 * M_PI)
			cbd->render.headbob = 0;
	}
	else //Reset walking animation
	{
		cbd->render.headbob -= cbd->mlx->delta_time;
		if (cbd->render.headbob < 0)
			cbd->render.headbob = 0;
	}
	//Player rotation
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= cbd->mapdata->width)
	{
		rotate_particles(cbd->particles, -pos.x);
		cbd->playerdata.dir = vec_rotate(cbd->playerdata.dir, cbd->mlx->delta_time * 3);
		cbd->playerdata.plane = vec_rotate(cbd->playerdata.plane, cbd->mlx->delta_time * 3);
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
	{
		rotate_particles(cbd->particles, pos.x);
		cbd->playerdata.dir = vec_rotate(cbd->playerdata.dir, -cbd->mlx->delta_time * 3);
		cbd->playerdata.plane = vec_rotate(cbd->playerdata.plane, -cbd->mlx->delta_time * 3);
	}
	//Resolve movement
	cbd->render.y_offset = (sin(cbd->render.headbob) * 10) + cbd->render.map_peak;
	cbd->playerdata.pos = potential_pos;
}
