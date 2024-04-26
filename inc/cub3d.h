/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 15:29:29 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/26 15:51:36 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>
# include <cbd_vec.h>
# include <cbd_render.h>
# include <cbd_parser.h>
# include <cbd_menu.h>

# define SUCCESS 0
# define FAILURE 1

typedef enum e_state
{
	STATE_MENU,
	STATE_GAME,
	STATE_BEHEAD,
}	t_state;

typedef struct s_beheading
{
	double	timer;
	bool	active;
	bool	sawing;
	t_vec2d	chainsaw_pos;
	t_vec2d	target_pos;
}	t_beheading;

typedef struct s_player
{
	enum e_player_state	{
		PLAYER_IDLE,
		PLAYER_WALKING,
		PLAYER_RUNNING,
		PLAYER_ATTACKING,
	}					t_player_state;
	t_vec2d				pos;
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
	enum e_player_state	state;
}	t_player;

typedef struct s_app
{
	t_particle	particles[N_PARTICLES];
	t_player	playerdata;
	t_render	render;
	t_menu		*menudata;
	t_map		*mapdata;
	t_hud		*hud;
	t_state		state;
	t_beheading	beheading;
	t_vec2d		mouse;
	t_vec2d		prev_mouse;
	mlx_t		*mlx;
	void		*audio;
	double		elapsed_time;
	bool		checkpoint;
}	t_app;

typedef struct s_audio	t_audio;

//		Utility
void		print_entities(t_entity *head);
void		print_2d(char **str);
void		print_debug_info(t_app *cub3d);
void		cleanup(t_app *app);
void		cleanup_map(t_map *map);

// 		Rendering
void		cbd_render(t_app *cbd);

//		Raycaster
t_ray		raycast(char **map, t_vec2d pos, t_vec2d dir);
void		cast_rays(char **map, t_render *render, t_player *p);

//		Game
bool		cbd_main(t_app *cbd);
bool		cbd_init(t_app *cbd);
void		cbd_loop(void *param);
void		update_timers(t_fx *fx, float dt);
void		update_entities(t_app *cbd);
void		move_entities(t_entity *ent, t_app *cbd);
void		cbd_init_input(t_app *cbd);
void		cbd_input(mlx_key_data_t keydata, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
void		mouse_input(t_app *cbd);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		destroy_wall(t_map *mapdata,
				const t_player *player, t_audio *audio);
void		reset_inventory(t_inventory *inv);
void	update_enemy(t_entity *ent, t_app *cbd);

// Beheading
void		behead(t_app *cbd);

//		Interaction / movement
void		move_player(t_app *cbd, float move_speed);
void		change_map(t_app *cbd);
void		rotate_player(t_player *playerdata,
				t_particle *particles, float angle);
void	update_item(t_entity *item, t_app *cbd);

//		Combat
void		dismember_enemy(t_app *cbd);
void		deal_damage(t_app *cbd);

//		Player.c
void		attack_player(t_entity *ent, t_player *playerdata, t_fx *fx);
void		update_player(t_player *playerdata, t_app *cbd);
void		escape_player(t_vec2d pos, t_vec2d dir, t_app *cbd);
void		update_headbob_animation(t_app *cbd);

//		Input.c
void		game_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio);

//		Init
mlx_image_t	*cbd_init_texture_img(mlx_t *mlx, char *path);
void		init_playerdata(t_player *playerdata, t_map *map);
void	init_sound_triggers(t_audio *audio, t_app *cbd);
t_inventory	*cbd_init_inventory(mlx_t *mlx);
bool		init_weapons(mlx_t *mlx, t_inventory *inv);
void		init_particles(t_particle *particles);
t_menu		*cbd_init_menu(mlx_t *mlx, t_map *map);

#endif //CUBER3D_H
