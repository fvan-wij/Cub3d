#include <cbd_audio.h>
#include <stdlib.h>

void	play_sound(t_audio *audio, uint8_t type)
{
	ma_sound_start(audio->sound[type]);
}

void	loop_sound(t_audio *audio, uint8_t type)
{
	ma_bool32 is_looping;

	is_looping = true;
	ma_sound_set_looping(audio->sound[type], is_looping);
	ma_sound_start(audio->sound[type]);
}

void	stop_sound(t_audio *audio, uint8_t type)
{
	ma_sound_stop(audio->sound[type]);
	ma_sound_seek_to_pcm_frame(audio->sound[type], 0);
}

static ma_sound	*init_sound(ma_engine *engine, const char *path)
{
	ma_sound	*sound;
	ma_result	err;

	sound = malloc(sizeof(ma_sound));
	if (!sound)
		return (NULL);
	err = ma_sound_init_from_file(engine, path, 0, NULL, NULL, sound);
	if (err != MA_SUCCESS)
		return (NULL);
	return (sound);
}

void	cbd_uninit_audio(t_audio *audio)
{
	int i;

	i = 0;
	while (i < SND_SIZE)
	{
		ma_sound_uninit(audio->sound[i]);
		i++;
	}
	ma_engine_uninit(audio->engine);
	free(audio);
}

t_audio	*cbd_init_audio(void)
{
	t_audio 	*game_audio;
	ma_result 	result;

	game_audio = malloc(sizeof(t_audio));
	if (!game_audio)
		return (NULL);
	game_audio->engine = malloc(sizeof(ma_engine));
	if (!game_audio->engine)
		return (free(game_audio), NULL);
	result = ma_engine_init(NULL, game_audio->engine);
	if (result != MA_SUCCESS)
		(free(game_audio), free(game_audio->engine), (void) NULL);
	game_audio->sound[SND_MUSIC] = init_sound(game_audio->engine, "./data/audio/ambient_music.mp3");
	game_audio->sound[SND_WALK] = init_sound(game_audio->engine, "./data/audio/step_3.mp3");
	game_audio->sound[SND_MENU] = init_sound(game_audio->engine, "./data/audio/menu.wav");
	game_audio->sound[SND_SEARCH] = init_sound(game_audio->engine, "./data/audio/search.mp3");
	game_audio->sound[SND_PUNCH] = init_sound(game_audio->engine, "./data/audio/punch.mp3");
	game_audio->sound[SND_TICK] = init_sound(game_audio->engine, "./data/audio/tick.mp3");
	ma_sound_set_volume(game_audio->sound[SND_TICK], 1.0f);
	ma_sound_set_volume(game_audio->sound[SND_SEARCH], 3.0f);
	ma_sound_set_volume(game_audio->sound[SND_PUNCH], 0.5f);
	ma_sound_set_volume(game_audio->sound[SND_WALK], 1.2f);
	game_audio->is_initialized = true;
	return (game_audio);
}
