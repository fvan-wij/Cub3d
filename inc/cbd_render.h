#ifndef CBD_RENDER_H
# define CBD_RENDER_H
# include <stdint.h>
# include <cbd_vec.h>
# include <MLX42.h>

//Window size
# define WIDTH 			1280
# define HEIGHT 		720
# define FOV 			90


//Colors
# define WHITE 		0xFFFFFFFF
# define OFF_WHITE	0xF0F0F0FF
# define RED 		0xFF0000FF
# define GREEN 		0x00FF00FF
# define BLUE 		0x0000FFFF

//Dimensions
# define TILESIZE 		64
# define MINIMAP_WIDTH	184
# define MINIMAP_HEIGHT	118
# define N_PARTICLES	40

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

//Animations
#define MAX_FRAMES 3

typedef struct s_animation_frame {
	mlx_image_t		*img;
	uint8_t			duration;
} t_animation_frame;

typedef struct s_animation {
	t_animation_frame		frames[MAX_FRAMES];
	uint8_t					n_frames;
	size_t					current_frame;
	size_t					frame_count;
	float					total_time;
	bool					loop;
}	t_animation;

typedef struct s_weapon {
	t_animation	*fire_animation;
	mlx_image_t	*img;
	uint8_t		type;
} t_weapon;

typedef struct s_inventory {
	enum e_inv_items {
		WPN_FIST,
		WPN_CHAINSAW,
		WPN_MAP,
		WPN_SIZE,
	} t_inv_items;
	t_weapon	weapons[WPN_SIZE];
	uint8_t		equipped;
}	t_inventory;

//HUD data
typedef struct s_hud {
	enum e_hud_items {
		HUD_MAP,
		HUD_OVERLAY,
		HUD_SIZE,
	} t_hud_items;
	mlx_image_t	*img[HUD_SIZE];
} t_hud;

//Color
int32_t	color(uint8_t r, uint8_t g, uint8_t b);
int32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//Draw
void	draw_hud(t_hud *hud);
void	draw_background(mlx_image_t *img, int32_t color);
void	draw_player(mlx_image_t *img);
void	draw_map(char **map, t_hud *hud, int width, int height);
void	draw_minimap(mlx_image_t *hud_map, t_vec2d pos, char **map, int width, int height);
void	draw_wall_strip(mlx_image_t *game, uint32_t color, int height, int x, float headbob, float map_peak);
void	draw_walls(mlx_image_t *game, t_ray *rays, float headbob, float map_peak);
void	draw_equipped_weapon(t_inventory *inv);

//Draw	shapes
void	draw_line(mlx_image_t *image, uint32_t color, t_vec2i p1, t_vec2i p2);
void	draw_square(mlx_image_t *image, uint32_t color, t_vec2i pos, t_vec2i dimension);
void	draw_noise_square(mlx_image_t *image, t_vec2i pos, t_vec2i dimension);
void	draw_circle(mlx_image_t *image, uint32_t color, t_vec2i pos, float r);

//Post processing
void	draw_gradient_bg(t_hud *hud);
void	draw_particles(mlx_image_t *game, t_particle *particles);

//Animation
void	play_weapon_animation(mlx_t	*mlx, t_inventory *inv);

#endif //CBD_RENDER_H
