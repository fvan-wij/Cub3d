#include <cub3d.h>
#include <cbd_audio.h>
#include <cbd_error.h>
#include <stdio.h>

void deal_fist_damage(t_app *cbd)
{
	t_audio *audio = cbd->audio;
	if (cbd->state == STATE_BEHEAD)
	{

		t_audio *audio = cbd->audio;
		audio->damage_is_dealt = true;
	}
	else if (cbd->playerdata.inv->equipped == WPN_FIST)
	{
		if ((cbd->playerdata.target_entity != NULL && cbd->playerdata.target_distance < 1.0))
		{
			cbd->render.fx.crt = true;
			cbd->render.fx.blood = true;
			cbd->playerdata.target_entity->health -= 4;
			if (cbd->playerdata.target_entity->enabled)
				dismember_enemy(cbd);
			audio->damage_is_dealt = true;
		}
}
}

void deal_chainsaw_damage(t_app *cbd)
{
	if (cbd->playerdata.inv->equipped != WPN_CHAINSAW || cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo <= 0)
		return;
	else if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
	{
		if (cbd->playerdata.target_entity != NULL && cbd->playerdata.target_distance < 1.0)
		{
			cbd->render.fx.crt = true;
			cbd->render.fx.blood = true;
			cbd->render.fx.splat = true;
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo -= cbd->mlx->delta_time * 5;
			cbd->playerdata.target_entity->health -= cbd->mlx->delta_time * 0.65;
			if (cbd->playerdata.target_entity->enabled)
				dismember_enemy(cbd);
		}
		else
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo-=cbd->mlx->delta_time * 10;
	}
}

void	update_timers(t_fx *fx, float dt)
{
	// Screen blood splatter timer
	if (fx->splat)
		fx->splat_timer -= dt * 1000;
	if (fx->splat_timer < 0)
	{
		fx->splat_timer = 150;
		fx->splat = false;
	}

	//Pulse timer
	fx->pulse_timer -= dt * 2;
	if (fx->pulse_timer < 0)
		fx->pulse_timer = 1000;
	//Screenshake
	if (fx->crt)
		fx->crt_timer -= dt * 1000;
	if (fx->crt_timer < 0)
	{
		fx->crt_timer = 100;
		fx->crt = false;
	}
}


t_entity *spawn_blood(t_entity *head, t_player *player, uint8_t limb)
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
	t_entity	*target;
	double		target_distance;

	target = cbd->playerdata.target_entity;
	target_distance = cbd->playerdata.target_distance;
	if (target->dead)
		return ;
	if (ft_strncmp(target->name, "vc", 2) == 0)
	{
		if (target->health % 10 == 0)
		{
			if (target->health <= 0)
			{
				target->animation.current_animation = 2;
				target->dead = true;
				target->speed = 0;
				target->health = 0;
				return;
			}
			target->animation.current_animation++;
			target->speed -= 0.5;
		}
	}
	if (ft_strncmp(target->name, "po", 2) == 0 && target_distance < 1.0)
	{
		if (!target->enabled)
			return ;
		if (target->health % 20 == 0)
		{
			target->speed-=0.15;
			if (target->limb <= 4)
				spawn_blood(cbd->mapdata->entities, &cbd->playerdata, target->limb);
			target->limb++;
			target->animation.current_animation = (target->limb * 2);
		}
		if (target->health < 20 && target->health > 0)
			cbd->state = STATE_BEHEAD;
		if (target->health <= 0)
		{
			target->health = 0;
			target->speed = 0;
		}
	}
}
