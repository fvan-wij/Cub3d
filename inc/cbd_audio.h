#ifndef CBD_AUDIO_H
# define CBD_AUDIO_H

# include "miniaudio.h"
# include "cbd_render.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum s_sounds {
	SND_WALK_SOLID,
	SND_WALK_GRASS,
	SND_MENU,
	SND_SEARCH,
	SND_MUSIC,
	SND_AMBIENT_MUSIC,
	SND_PUNCH,
	SND_TICK,
	SND_WALL1,
	SND_WALL2,
	SND_WALL3,
	SND_GUTS,
	SND_TAKE_DAMAGE,
	SND_NEAR_DEATH,
	SND_SAW,
	SND_SAW_IDLE,
	SND_TV_NOISE,
	SND_TV_BYE,
	SND_TV_JAZZ,
	SND_TV_RICKROLL,
	SND_TV_SURREAL,
	SND_AMBIENT_LAUGH,
	SND_IMPACT,
	SND_IMPACT2,
	SND_IMPACT3,
	SND_CROWS,
	SND_CHASE,
	SND_LAUGH,
	SND_NO_FUEL,
	SND_NO_FUEL2,
	SND_PICKUP,
	SND_GAME_OVER,
	SND_BUSH,
	SND_NOONOO,
	SND_SUCK,
	SND_PO_TRIGGER,
	SND_SIZE,
} t_sounds;

enum e_player_state;

typedef struct s_audio {
	ma_sound	*sound[SND_SIZE];
	ma_engine	*engine;
	bool		is_initialized;
	t_entity	*tv;
	t_entity	*trigger1;
	t_entity	*trigger2;
	t_entity	*enemy;
	t_entity	*vc;
	bool		t1;
	bool		t2;
	bool		pickup;
	bool		damage;
	bool		is_dead;
	bool		chase;
	bool		checkpoint;
	bool		damage_is_dealt;
	bool		boss_trigger;
	bool		near_death;
	bool		secret;
	uint8_t		channel;
}	t_audio;

t_audio	*cbd_init_audio(void);
void	cbd_uninit_audio(t_audio *audio);
void	play_sound(t_audio *audio, uint8_t type, float volume, float pitch);
void	play_walk_sound(t_audio *audio, float dt);
void	loop_sound(t_audio *audio, uint8_t type, bool alternate);
void	stop_sound(t_audio *audio, uint8_t type);
void	reset_sounds(t_audio *audio);
void	update_game_audio(t_audio *audio, t_inventory *inv, enum e_player_state state, int health);
void	update_game_audio_dark_secret(t_audio *audio, t_inventory *inv, enum e_player_state state, int health);
void	update_game_audio_behead(t_audio *audio, t_inventory *inv, enum e_player_state state, int health);
void	update_menu_audio(t_audio *audio, t_app *cbd);
#endif
