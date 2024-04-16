#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <stdlib.h>

void	move_particles(t_particle *particles, float x, float y)
{
	int i;

	i = 0;
	while (i < N_PARTICLES)
	{
		particles[i].p.x += x;
		particles[i].p.y += y;
		i++;
	}
}

void	rotate_particles(t_particle *particles, float dir)
{
	int i;

	i = 0;
	dir *=4;
	while (i < N_PARTICLES)
	{
		particles[i].p.x += dir;
		i++;
	}
}

void	resolve_particles(t_particle *particles, int8_t dir)
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
		particles[i].p.y += dir;
		particles[i].p.x += particles[i].dir.x * 5;
		if (particles[i].size.x < 0 || particles[i].size.y < 0)
		{
			particles[i].size = particles[i].reset;
			particles[i].p = vec_assign((float) rand() / (float)RAND_MAX * WIDTH, (float) rand() / (float)RAND_MAX * HEIGHT);
		}
		i++;
	}
}
