#include <cbd_audio.h>
#include <cub3d.h>

void	update_menu_audio(t_audio *audio, t_app *cbd)
{
	if (cbd->menudata->state == GAME_OVER || cbd->menudata->state == GAME_WON)
	{
		stop_sound(audio, SND_SAW_IDLE);
		stop_sound(audio, SND_SAW);
		stop_sound(audio, SND_NEAR_DEATH);
		stop_sound(audio, SND_NO_FUEL2);
		stop_sound(audio, SND_NOONOO);
		stop_sound(audio, SND_SUCK);
		stop_sound(audio, SND_MUSIC);
		stop_sound(audio, SND_CHASE);
		stop_sound(audio, SND_LAUGH);
		stop_sound(audio, SND_WALK_GRASS);
		stop_sound(audio, SND_WALK_SOLID);
		stop_sound(audio, SND_AMBIENT_LAUGH);
		stop_sound(audio, SND_AMBIENT_MUSIC);
		loop_sound(audio, SND_GAME_OVER, false);
	}
	else if (cbd->menudata->state == MAIN)
	{
		stop_sound(audio, SND_MUSIC);
		stop_sound(audio, SND_AMBIENT_LAUGH);
		stop_sound(audio, SND_AMBIENT_MUSIC);
		stop_sound(audio, SND_GAME_OVER);
		loop_sound(audio, SND_MENU, false);
	}
}
