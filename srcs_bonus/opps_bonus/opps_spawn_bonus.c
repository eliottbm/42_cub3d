/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opps_spawn_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:01:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/19 15:28:22 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline int	cond_span(char **map, int (*pos)[2], t_data *data)
{
	if (correct_pos(map, (*pos)[1], (*pos)[0])
		&& ((*pos)[1] != (int)floor(data->player.pos[1])
		&& (*pos)[0] != (int)floor(data->player.pos[0])))
		return (1);
	return (0);
}

static int	_spawn_one_opps(t_data *data, int (*pos)[2])
{
	int	player[2];

	player[1] = (int)floor(data->player.pos[1]);
	player[0] = (int)floor(data->player.pos[0]);
	if ((player[1] < OPPS_AWAY && ft_ultimate_len(data->map)
			< player[1] + OPPS_AWAY)
		&& (player[0] < OPPS_AWAY && player[0] + OPPS_AWAY
			> (int)ft_strlen(data->map[player[1]])))
		return (-1);
	if (player[1] < OPPS_AWAY)
		(*pos)[1] = player[1] + (rand()
				% (ft_ultimate_len(data->map) - player[1] + 1));
	else
		(*pos)[1] = player[1] - (rand() % (player[1] + 1));
	if (player[0] < OPPS_AWAY)
		(*pos)[0] = player[0] + (rand()
				% ((int)ft_ultimate_len(data->map) - player[0]));
	else
		(*pos)[0] = player[0] - (rand() % (player[0] + 1));
	if (cond_span(data->map, pos, data))
	{
		if (data->map[(*pos)[0]][(*pos)[1]] == '0')
			return (data->map[(*pos)[0]][(*pos)[1]] = 'G', 1);
	}
	return (0);
}

int	_spawn_opps(t_data *data)
{
	int	i;
	int	j;
	int	rval;
	int	pos[2];

	rval = 0;
	i = data->nb_opps - 1;
	while (++i < OPPS_NBR)
	{
		j = -1;
		while (++j < OPPS_AWAY + 1)
		{
			rval = _spawn_one_opps(data, &pos);
			if (rval == 1)
			{
				data->nb_opps++;
				if (add_gengar_back(data, pos))
					return (1);
				break ;
			}
			if (rval == -1)
				return (0);
		}
	}
	return (0);
}
