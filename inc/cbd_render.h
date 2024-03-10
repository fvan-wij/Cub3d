#ifndef CBD_RENDER_H
# define CBD_RENDER_H
# include <stdint.h>
# include <cbd_vec.h>
# include <MLX42.h>

//Colors
# define WHITE 		0xFFFFFFFF
# define OFF_WHITE	0xF0F0F0FF
# define RED 		0xFF0000FF
# define GREEN 		0x00FF00FF
# define BLUE 		0x0000FFFF

//Dimensions
# define TILES 			(64 + 64)
# define TILESIZE 		WIDTH / TILES
# define MAPSIZE		WIDTH - (TILESIZE * 16)
# define RADARW			626
# define RADARH			448
# define N_PARTICLES	25
# define WIDTH 			1280
# define HEIGHT 		720
# define FOV 			90

typedef struct s_bresenham
{
	int			error[2];
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			cx;
	int			cy;
	int			y;
	int			x;
}	t_bresenham;

typedef struct s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}	t_line;

typedef union s_rgba
{
	int32_t	color;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

typedef struct s_ray {
	t_vec2d	dir;
	t_vec2d intersection;
	double	wall_dist;
	uint8_t	side;
} t_ray;

typedef	struct s_particle {
	t_vec2d	p;
	t_vec2d dir;
	t_vec2d size;
	t_vec2d	reset;
} t_particle;

typedef struct s_hud {
	enum e_hud_id {
		HUD_MAP,
		WPN_MAP,
		WPN_FIST,
		WPN_CHAINSAW,
		HUD_OVERLAY,
		HUD_SIZE,
	} t_hud_id;
	mlx_image_t	*img[HUD_SIZE];
	int8_t equipped;
} t_hud;

//Color
int32_t	color(uint8_t r, uint8_t g, uint8_t b);

//Draw
void	draw_hud(t_hud *hud);
void	draw_background(mlx_image_t *img, int32_t color);
void	draw_player(char **map, mlx_image_t *img, t_vec2d pos, t_vec2d dir);
void	draw_map(char **map, t_hud *hud, int width, int height);
void	draw_wall_strip(mlx_image_t *game, uint32_t color, int height, int x, float headbob, float map_peak);
void	draw_walls(mlx_image_t *game, t_ray *rays, float headbob, float map_peak);
void	draw_line(mlx_image_t *image, uint32_t color, t_vec2i p1, t_vec2i p2);
void	draw_square(mlx_image_t *image, uint32_t color, t_vec2i pos, t_vec2i dimension);
void	draw_circle(mlx_image_t *image, uint32_t color, t_vec2i pos, float r);

//Post processing
void	draw_gradient_bg(t_hud *hud);
void	draw_particles(mlx_image_t *game, t_particle *particles);

#endif //CBD_RENDER_H
