#include <cbd_audio.h>
#include <stdlib.h>
#include <libft.h>

void	play_sound(t_audio *audio, uint8_t type, float volume, float pitch)
{
	ma_sound_seek_to_pcm_frame(audio->sound[type], 0);
	ma_sound_set_pitch(audio->sound[type], pitch);
	ma_sound_set_volume(audio->sound[type], volume);
	ma_sound_start(audio->sound[type]);
}

static void	alternate_pitch(t_audio *audio, uint8_t type)
{
	static float 	timer;
	static int		alternate;

	timer -= 0.25;
	if (alternate == 0)
		ma_sound_set_pitch(audio->sound[type], 1.05f);
	else
		ma_sound_set_pitch(audio->sound[type], 0.97f);
	if (timer < 0)
	{
		alternate++;
		timer = 1;
	}
	if (alternate > 1)
		alternate = 0;
}

void	loop_sound(t_audio *audio, uint8_t type, bool alternate)
{
	ma_bool32 is_looping;

	is_looping = true;
	if (ma_sound_is_playing(audio->sound[type]))
		return ;
	if (alternate)
		alternate_pitch(audio, type);
	ma_sound_set_looping(audio->sound[type], is_looping);
	ma_sound_start(audio->sound[type]);
}

void	stop_sound(t_audio *audio, uint8_t type)
{
	ma_sound_stop(audio->sound[type]);
	ma_sound_seek_to_pcm_frame(audio->sound[type], 0);
}

void	reset_sounds(t_audio *audio)
{
	size_t i;

	i = 0;
	while (i < SND_SIZE)
	{
		ma_sound_stop(audio->sound[i]);
		ma_sound_seek_to_pcm_frame(audio->sound[i], 0);
		i++;
	}
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

	game_audio = ft_calloc(1, sizeof(t_audio));
	if (!game_audio)
		return (NULL);
	game_audio->engine = malloc(sizeof(ma_engine));
	if (!game_audio->engine)
		return (free(game_audio), NULL);
	result = ma_engine_init(NULL, game_audio->engine);
	if (result != MA_SUCCESS)
		(free(game_audio), free(game_audio->engine), (void) NULL);
	game_audio->sound[SND_MUSIC] = init_sound(game_audio->engine, "./data/audio/ambient_music2.mp3");
	ma_sound_set_volume(game_audio->sound[SND_MUSIC], 0.65f);

	game_audio->sound[SND_WALK_GRASS] = init_sound(game_audio->engine, "./data/audio/step_grass.mp3");
	game_audio->sound[SND_WALK_SOLID] = init_sound(game_audio->engine, "./data/audio/step_solid.mp3");
	ma_sound_set_volume(game_audio->sound[SND_WALK_SOLID], 0.8f);
	ma_sound_set_volume(game_audio->sound[SND_WALK_GRASS], 0.6f);

	game_audio->sound[SND_MENU] = init_sound(game_audio->engine, "./data/audio/menu.wav");
	game_audio->sound[SND_SEARCH] = init_sound(game_audio->engine, "./data/audio/search.mp3");
	game_audio->sound[SND_PUNCH] = init_sound(game_audio->engine, "./data/audio/punch.mp3");
	game_audio->sound[SND_GUTS] = init_sound(game_audio->engine, "./data/audio/guts.mp3");
	game_audio->sound[SND_TAKE_DAMAGE] = init_sound(game_audio->engine, "./data/audio/take_damage.mp3");
	game_audio->sound[SND_NEAR_DEATH] = init_sound(game_audio->engine, "./data/audio/near_death.mp3");

	game_audio->sound[SND_TICK] = init_sound(game_audio->engine, "./data/audio/tick.mp3");

	game_audio->sound[SND_SAW] = init_sound(game_audio->engine, "./data/audio/saw_loop2.mp3");
	game_audio->sound[SND_SAW_IDLE] = init_sound(game_audio->engine, "./data/audio/saw_idle2.mp3");
	ma_sound_set_volume(game_audio->sound[SND_SAW], 3.0f);
	ma_sound_set_volume(game_audio->sound[SND_SAW_IDLE], 0.3f);

	game_audio->sound[SND_WALL1] = init_sound(game_audio->engine, "./data/audio/wall_destruction/wall2.mp3");
	game_audio->sound[SND_WALL2] = init_sound(game_audio->engine, "./data/audio/wall_destruction/wall3.mp3");
	game_audio->sound[SND_WALL3] = init_sound(game_audio->engine, "./data/audio/wall_destruction/wall1.mp3");

	game_audio->sound[SND_AMBIENT_LAUGH] = init_sound(game_audio->engine, "./data/audio/ambient_laugh.mp3");
	game_audio->sound[SND_AMBIENT_MUSIC] = init_sound(game_audio->engine, "./data/audio/ambient_music.mp3");
	ma_sound_set_volume(game_audio->sound[SND_AMBIENT_MUSIC], 1.0f);
	game_audio->sound[SND_IMPACT] = init_sound(game_audio->engine, "./data/audio/impact.mp3");
	game_audio->sound[SND_IMPACT2] = init_sound(game_audio->engine, "./data/audio/impact2.mp3");
	game_audio->sound[SND_CHASE] = init_sound(game_audio->engine, "./data/audio/chase.mp3");
	game_audio->sound[SND_GAME_OVER] = init_sound(game_audio->engine, "./data/audio/chase_stop.mp3");
	game_audio->sound[SND_LAUGH] = init_sound(game_audio->engine, "./data/audio/laugh.mp3");

	game_audio->sound[SND_NO_FUEL] = init_sound(game_audio->engine, "./data/audio/no_fuel.mp3");
	game_audio->sound[SND_NO_FUEL2] = init_sound(game_audio->engine, "./data/audio/no_fuel2.mp3");

	game_audio->sound[SND_PICKUP] = init_sound(game_audio->engine, "./data/audio/item_pickup.mp3");

	game_audio->sound[SND_TV_NOISE] = init_sound(game_audio->engine, "./data/audio/tv_noise.mp3");
	game_audio->sound[SND_TV_BYE] = init_sound(game_audio->engine, "./data/audio/tv_bye.mp3");
	game_audio->sound[SND_TV_JAZZ] = init_sound(game_audio->engine, "./data/audio/channel2.mp3");
	game_audio->sound[SND_TV_RICKROLL] = init_sound(game_audio->engine, "./data/audio/channel3.mp3");
	game_audio->sound[SND_TV_SURREAL] = init_sound(game_audio->engine, "./data/audio/channel4.mp3");

	game_audio->sound[SND_IMPACT3] = init_sound(game_audio->engine, "./data/audio/impact3.mp3");
	game_audio->sound[SND_CROWS] = init_sound(game_audio->engine, "./data/audio/crows.mp3");
	game_audio->sound[SND_BUSH] = init_sound(game_audio->engine, "./data/audio/bush.mp3");
	game_audio->sound[SND_NOONOO] = init_sound(game_audio->engine, "./data/audio/noonoo.mp3");
	game_audio->sound[SND_SUCK] = init_sound(game_audio->engine, "./data/audio/suck.mp3");
	game_audio->sound[SND_PO_TRIGGER] = init_sound(game_audio->engine, "./data/audio/po_trigger.mp3");

	ma_sound_set_volume(game_audio->sound[SND_NEAR_DEATH], 0.65f);
	ma_sound_set_volume(game_audio->sound[SND_SUCK], 0.30f);

	game_audio->is_initialized = true;
	game_audio->secret = false;
	game_audio->damage_is_dealt = false;
	game_audio->boss_trigger = false;
	game_audio->near_death = false;
	return (game_audio);
}
