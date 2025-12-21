/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:49:53 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/19 15:09:16 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	get_isprite(t_data *data, char c)
{
	int	i;

	i = 0;
	if (c == 'K')
	{
		while (data->sprites[i].sp_k_or_g != 'K' && i < OPPS_NBR + 1)
			i++;
	}
	else
	{
		while ((data->sprites[i].sp_k_or_g != 'G'
				|| data->sprites[i].sp_isview != 0) && i < OPPS_NBR + 1)
			i++;
	}
	return (i);
}

static void	add_sprite(t_data *data, t_ray *ray, char c)
{
	int		i;
	t_opps	*e;
	t_play	pl;

	i = get_isprite(data, c);
	pl = data->player;
	if (c == 'G')
	{
		e = _which_gengar(data, ray->pos[1], ray->pos[0]);
		if (!e)
			return (printf("on quitte\n\n"), (void)1);
		e->seen = 1;
		data->sprites[i].sp_pos[0] = e->pos[0];
		data->sprites[i].sp_pos[1] = e->pos[1];
	}
	data->sprites[i].sp_dist = ((pl.pos[1] - data->sprites[i].sp_pos[1])
			* (pl.pos[1] - data->sprites[i].sp_pos[1])
			+ (pl.pos[0] - data->sprites[i].sp_pos[0])
			* (pl.pos[0] - data->sprites[i].sp_pos[0]));
	data->sprites[i].sp_isview = 1;
}

static inline int	is_sprite(t_data *data, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < OPPS_NBR + 1)
	{
		if (data->sprites[i].sp_isview == 1
			&& (int)data->sprites[i].sp_pos[0] == ray->pos[0]
			&& (int)data->sprites[i].sp_pos[1] == ray->pos[1])
			return (1);
		i++;
	}
	return (0);
}

static inline void	dda_checks(t_data *data, t_ray *ray, char **map, int isrun)
{
	if (map[ray->pos[0]][ray->pos[1]] == '1'
		|| map[ray->pos[0]][ray->pos[1]] == '2'
		|| map[ray->pos[0]][ray->pos[1]] == 'X'
		|| (map[ray->pos[0]][ray->pos[1]] == 'D'
		&& (!data->d_anim.da_isrun || !is_lookdoor(data))))
		ray->hit = 1;
	if (isrun && map[ray->pos[0]][ray->pos[1]] == 'D'
		&& data->d_anim.da_isrun > 0 && is_lookdoor(data))
		save_draw_infos(*data, &data->d_draw, data->d_anim.da_img);
	if (!isrun && map[ray->pos[0]][ray->pos[1]] == 'D')
		ray->hit = ((data->d_anim.da_check) = 1);
	if (isrun && (map[ray->pos[0]][ray->pos[1]] == 'K'
		|| map[ray->pos[0]][ray->pos[1]] == 'G') && !is_sprite(data, ray))
		add_sprite(data, ray, map[ray->pos[0]][ray->pos[1]]);
}

void	run_dda(t_data *data, t_ray *ray, char **map, int isrun)
{
	while (!ray->hit)
	{
		if (ray->dist[1] < ray->dist[0])
		{
			ray->dist[1] += ray->delta[1];
			ray->pos[1] += ray->step[1];
			ray->side = 0;
		}
		else
		{
			ray->dist[0] += ray->delta[0];
			ray->pos[0] += ray->step[0];
			ray->side = 1;
		}
		dda_checks(data, ray, map, isrun);
	}
}
