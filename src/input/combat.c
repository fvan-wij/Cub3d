#include <cub3d.h>
#include <cbd_audio.h>
#include <cbd_error.h>

static t_entity *spawn_blood(t_entity *head, t_player *player, uint8_t limb)
{
	t_entity *node;
	t_entity *curr;

	node = ft_calloc(1, sizeof(t_entity));
	if (!node)
		return (cbd_error(ERR_ALLOC), head);
	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->next = NULL;
	node->name = ft_strdup("blood");
	node->pos = vec_assign(player->pos.x + player->dir.x, player->pos.y + player->dir.y);
	node->type = ENTITY_DECOR;
	node->texture = mlx_load_png("./data/textures/sprites/limbs3.png");
	node->frame_width = 128;
	node->frame_height = 128;
	node->enabled = true;
	node->animation = load_animation(node->texture, node->frame_width, node->frame_height);
	node->animation.current_animation = limb;
	return (head);
}

void	dismember_enemy(t_app *cbd)
{
	static int	limb;
	static int	i;
	t_entity	*target;
	double		target_distance;

	target = cbd->playerdata.target_entity;
	target_distance = cbd->playerdata.target_distance;
	if (ft_strncmp(target->name, "po", 2) == 0 && target_distance < 0.5)
	{
		if (i % 25 == 0)
		{
			target->health-=2;
			target->speed-=0.2;
			if (limb <= 4)
				spawn_blood(cbd->mapdata->entities, &cbd->playerdata, limb);
			limb++;
		}
		if (target->health <= 0)
		{
			target->health = 0;
			target->speed = 0;
		}
		cbd->render.fx.splat = true;
		i++;
	}
}

