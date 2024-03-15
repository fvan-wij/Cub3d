#include <cub3d.h>

void	render_sprites(t_render *render, t_map *map, t_player *player)
{
	render->sprite = malloc(sizeof(t_sprite) * map->sprite_count);
}
