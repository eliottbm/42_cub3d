/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:25:12 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/02 17:17:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	flood_fill(char **map, char tofind, int posx, int posy)
{
	if (!correct_pos(map, posx, posy))
		return (0);
	if (map[posy][posx] == '1' || (map[posy][posx] == '2')
		|| (map[posy][posx] == 'V'))
		return (0);
	if (map[posy][posx] == tofind)
		return (1);
	map[posy][posx] = 'V';
	if (flood_fill(map, tofind, posx + 1, posy)
		|| flood_fill(map, tofind, posx - 1, posy)
		|| flood_fill(map, tofind, posx, posy + 1)
		|| flood_fill(map, tofind, posx, posy - 1))
		return (1);
	else
		return (0);
}

static void	_spawn_keys3(t_data *data, int (*pos)[2], int (*player)[2], int i)
{
	if (((*player))[1] < (KEY_AWAY - i))
		(*pos)[1] = (*player)[1] + (rand()
				% (ft_strlen(data->map[(*player)[0]]) - (*player)[1]));
	else
		(*pos)[1] = (*player)[1] - (rand() % ((*player)[1] + 1));
	if ((*player)[0] < (KEY_AWAY - i))
		(*pos)[0] = (*player)[0] + (rand()
				% ((int)ft_ultimate_len(data->map) - (*player)[0]));
	else
		(*pos)[0] = (*player)[0] - (rand() % ((*player)[0] + 1));
}

static int	_spawn_keys2(t_data *data, int i)
{
	int		player[2];
	int		pos[2];
	char	**map_copy;

	player[1] = (int)floor(data->player.pos[1]);
	player[0] = (int)floor(data->player.pos[0]);
	if ((player[0] < (KEY_AWAY - i) && ft_ultimate_len(data->map)
			< player[0] + (KEY_AWAY - i))
		&& (player[1] < (KEY_AWAY - i) && player[1] + (KEY_AWAY - 1)
			> (int)ft_strlen(data->map[player[0]])))
		return (-1);
	_spawn_keys3(data, &pos, &player, i);
	if ((data->map[pos[0]][pos[1]] == '0')
		&& (_available_ncell(data, pos)))
	{
		map_copy = ft_copy_tab(data->map);
		if (!map_copy)
			return (1);
		map_copy[pos[0]][pos[1]] = 'K';
		if (flood_fill(map_copy, 'K', player[1], player[0]))
			return (ft_free_split(map_copy),
				data->map[pos[0]][pos[1]] = 'K', 2);
		ft_free_split(map_copy);
	}
	return (0);
}

int	_spawn_keys(t_data *data)
{
	int	i;
	int	k;
	int	res;

	k = 0;
	i = 0;
	while (k < 5)
	{
		i = 0;
		while (i < KEY_AWAY)
		{
			res = _spawn_keys2(data, i);
			if (res == 1)
				return (1);
			if (res == 2)
				return (0);
			i++;
		}
		k++;
	}
	data->player.keys = 1;
	return (0);
}

int	spawn_exit_keys(t_data *data)
{
	if (spawn_the_exit(data) == 1)
		return (1);
	if (_spawn_keys(data) == 1)
		return (1);
	return (0);
}
