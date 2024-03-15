#ifndef CBD_AUDIO_H
# define CBD_AUDIO_H

# include "miniaudio.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum s_sounds {
	SND_WALK,
	SND_MENU,
	SND_SEARCH,
	SND_MUSIC,
	SND_PUNCH,
	SND_TICK,
	SND_SIZE,
} t_sounds;

typedef struct s_audio {
	ma_sound	*sound[SND_SIZE];
	ma_engine	*engine;
	bool		is_initialized;
}	t_audio;

t_audio	*cbd_init_audio(void);
void	cbd_uninit_audio(t_audio *audio);
void	play_sound(t_audio *audio, uint8_t type);
void	loop_sound(t_audio *audio, uint8_t type);
void	stop_sound(t_audio *audio, uint8_t type);

#endif
