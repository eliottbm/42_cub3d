/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:21 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/11 17:33:29 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	correct_pos(char **map, int x, int y)
{
	if (!map)
		return (0);
	if ((y >= 0 && y < ft_ultimate_len(map)
			&& (x >= 0 && x < (int)ft_strlen(map[y]))))
		return (1);
	return (0);
}

int	is_cellav(t_data *data, int x, int y)
{
	if (!correct_pos(data->map, x, y))
		return (0);
	if (data->map[y][x] == '0')
		return (1);
	if (data->map[y][x] == 'D'
		&& data->d_anim.da_isdone
		&& y == data->d_anim.da_doorpos[0]
		&& x == data->d_anim.da_doorpos[1])
		return (1);
	if (data->map[y][x] == 'K')
		return (1);
	if (data->map[y][x] == 'X' && data->player.keys)
		return (1);
	if (data->map[y][x] == 'G')
		return (1);
	return (0);
}
