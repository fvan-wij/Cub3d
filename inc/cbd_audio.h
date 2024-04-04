#ifndef CBD_AUDIO_H
# define CBD_AUDIO_H

#include "cbd_render.h"
# include "miniaudio.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum s_sounds {
	SND_WALK_SOLID,
	SND_WALK_GRASS,
	SND_MENU,
	SND_SEARCH,
	SND_MUSIC,
	SND_PUNCH,
	SND_TICK,
	SND_WALL1,
	SND_WALL2,
	SND_WALL3,
	SND_GUTS,
	SND_SAW,
	SND_SAW_IDLE,
	SND_TV_NOISE,
	SND_AMBIENT_LAUGH,
	SND_IMPACT,
	SND_IMPACT2,
	SND_SIZE,
} t_sounds;

typedef struct s_audio {
	ma_sound	*sound[SND_SIZE];
	ma_engine	*engine;
	bool		is_initialized;
	t_entity	*tv;
	t_entity	*trigger1;
	bool		t1;
}	t_audio;

t_audio	*cbd_init_audio(void);
void	cbd_uninit_audio(t_audio *audio);
void	play_sound(t_audio *audio, uint8_t type, float volume);
void	play_walk_sound(t_audio *audio, float dt);
void	loop_sound(t_audio *audio, uint8_t type, bool alternate);
void	stop_sound(t_audio *audio, uint8_t type);

#endif
