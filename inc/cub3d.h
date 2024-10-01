#ifndef CUB3D_H
# define CUB3D_H

// # include "../lib/MLX42/include/MLX42/MLX42.h"
// # include <../lib/libft/libft.h>

# include <MLX42.h>
# include <libft.h>
# include <cbd_vec.h>
# include <cbd_render.h>
# include <cbd_parser.h>
# include <cbd_menu.h>

# define SUCCESS 0
# define FAILURE 1

typedef enum e_state {
	STATE_MENU,
	STATE_GAME,
	STATE_BEHEAD,
} t_state;

typedef struct s_beheading {
	double	timer;
	bool	active;
	bool	sawing;
	t_vec2d	chainsaw_pos;
	t_vec2d	target_pos;
}	t_beheading;

typedef struct s_checkpoint_state {
	int			health;
	int			ammo;
	t_inventory inventory;
} t_checkpoint_state;

typedef struct s_player {
	enum e_player_state {
		PLAYER_IDLE,
		PLAYER_WALKING,
		PLAYER_RUNNING,
		PLAYER_ATTACKING,
	} t_player_state;
	t_vec2d 			pos;
	t_vec2d				dir;
	t_vec2d				plane;
	float				scalar;
	float				headbob;
	float				head_height;
	float				map_peak;
	t_ray				rays[WIDTH];
	double				target_distance;
	t_entity			*target_entity;
	t_inventory			*inv;
	double				i_time; //Invincibility timer
	int					health;
	enum e_player_state state;
}	t_player;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	space;
	bool	shift;
	bool	left;
	bool	right;
	bool	one;
	bool	two;
	bool	map;
} t_keys;

typedef struct s_app {
	t_particle 	particles[N_PARTICLES];
	t_player 	playerdata;
	t_render	render;
	t_menu		*menudata;
	t_map		*mapdata;
	t_hud		*hud;
	t_state		state;
	t_beheading	beheading;
	t_vec2d		mouse;
	t_vec2d		prev_mouse;
	t_checkpoint_state checkpoint_state;
	t_keys		*keys;
	mlx_t		*mlx;
	void		*audio;
	double		elapsed_time;
	bool		checkpoint;
}	t_app;

typedef struct s_audio t_audio;

//		Utility
void	print_entities(t_entity *head);
void	print_2d(char **str);
void	print_debug_info(t_app *cub3d);
void	cleanup(t_app *app);
void	cleanup_map(t_map *map);

// 		Rendering
void	cbd_render(t_app *cbd);

//		Raycaster
t_ray	raycast(char **map, t_vec2d pos, t_vec2d dir);
void	cast_rays(char **map, t_render *render, t_player *p);

//		Game
bool	cbd_init(t_app *cbd);
void	cbd_loop(void *param);
void	update_timers(t_fx *fx, float dt);
void	update_entities(t_app *cbd);
void	move_entities(t_entity *ent, t_app *cbd);
void	cbd_init_input(t_app *cbd);
void	cbd_input(mlx_key_data_t keydata, void *param);
void	cursor_hook(double xpos, double ypos, void* param);
void	mouse_input(t_app *cbd);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void	destroy_wall(t_map *mapdata, t_player *player, t_audio *audio);
void	reset_inventory(t_inventory *inv);

// Beheading
void	behead(t_app *cbd);

//		Interaction / movement
void	move_player(t_app *cbd);
void	change_map(t_app *cbd);
void	rotate_player(t_player *playerdata, t_particle *particles, float angle);

//		Combat
void	dismember_enemy(t_app *cbd);
void 	deal_chainsaw_damage(t_app *cbd);
void 	deal_fist_damage(t_app *cbd);

//		Player.c
void	attack_player(t_entity *ent, t_player *playerdata, t_fx *fx);
void	update_player(t_player *playerdata, t_app *cbd);
void	escape_player(t_vec2d pos, t_vec2d dir, t_app *cbd);

//		Init
mlx_image_t *cbd_init_texture_img(mlx_t *mlx, char *path);
void	init_playerdata(t_player *playerdata, t_map *map);

//		Input
void	menu_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio);
void	game_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio);
void 	change_tv_channel(t_audio *audio, mlx_key_data_t keydata);
void	app_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio);



#endif //CUBER3D_H
