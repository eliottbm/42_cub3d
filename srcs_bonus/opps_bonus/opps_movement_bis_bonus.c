/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opps_movement_bis_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:30:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:30:25 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	suce_pas_le_mur(t_data *data, int x_y, int way, int (*pos)[2])
{
	int	uposu[2];

	if (x_y == 1)
	{
		uposu[0] = (*pos)[0];
		if (way == 1)
			uposu[1] = (*pos)[1] + 1;
		else
			uposu[1] = (*pos)[1] + 1;
	}
	else
	{
		uposu[1] = (*pos[1]);
		if (way == 1)
			uposu[0] = (*pos)[0] + 1;
		else
			uposu[0] = (*pos)[0] - 1;
	}
	return (correct_pos(data->map, uposu[1],
			uposu[0]) && data->map[uposu[0]][uposu[1]] == '1');
}

int	stay_away_fw(t_data *data, int x_y, int way, t_opps *ops)
{
	int				pos[2];
	const double	speed = O_SPEED * data->player.m_speed;

	pos[0] = (int)floor(ops->pos[0]);
	pos[1] = (int)floor(ops->pos[1]);
	if (!suce_pas_le_mur(data, x_y, way, &pos))
		return (0);
	if (x_y == 1)
	{
		if (((int)((ops->pos[1]
					+ (speed * way) - (int)ops->pos[1]) * 10) % 10) >= 5)
			return (ops->pos[1] = (int)floor(ops->pos[1]) + 0.5, 1);
	}
	else
	{
		if (((int)((ops->pos[0]
					+ (speed * way) - (int)ops->pos[0]) * 10) % 10) >= 5)
			return (ops->pos[0] = (int)floor(ops->pos[0]) + 0.5, 1);
	}
	return (0);
}
