/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:56:39 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/18 15:57:01 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	_isexitbetweenwalls(t_data *data, int pos[2])
{
	if ((correct_pos(data->map, pos[1] - 1, pos[0])
			&& data->map[pos[0]][pos[1] - 1] == '1')
		&& (correct_pos(data->map, pos[1] + 1, pos[0])
		&& data->map[pos[0]][pos[1] + 1] == '1'))
		return (1);
	else if ((correct_pos(data->map, pos[1], pos[0] - 1)
			&& data->map[pos[0] - 1][pos[1]] == '1')
		&& (correct_pos(data->map, pos[1], pos[0] + 1)
		&& data->map[pos[0] + 1][pos[1]] == '1'))
		return (1);
	return (0);
}

int	_available_ncell(t_data *data, int pos[2])
{
	if (!_isexitbetweenwalls(data, pos))
		return (0);
	if ((correct_pos(data->map, pos[1] + 1, pos[0])
			&& data->map[pos[0]][pos[1] + 1] == 'D')
			|| (correct_pos(data->map, pos[1] - 1, pos[0])
		&& data->map[pos[0]][pos[1] - 1] == 'D')
		|| (correct_pos(data->map, pos[1], pos[0] + 1)
		&& data->map[pos[0] + 1][pos[1]] == 'D')
		|| (correct_pos(data->map, pos[1], pos[0] - 1)
		&& data->map[pos[0] - 1][pos[1]] == 'D'))
		return (0);
	if ((correct_pos(data->map, pos[1] + 1, pos[0])
			&& data->map[pos[0]][pos[1] + 1] == '0')
			|| (correct_pos(data->map, pos[1] - 1, pos[0])
		&& data->map[pos[0]][pos[1] - 1] == '0')
		|| ((correct_pos(data->map, pos[1], pos[0] + 1)
		&& data->map[pos[0] + 1][pos[1]] == '0'))
		|| (correct_pos(data->map, pos[1], pos[0] - 1)
		&& data->map[pos[0] - 1][pos[1]] == '0'))
		return (1);
	return (0);
}

static void	_spawn_exit3(t_data *data, int (*pos)[2], int (*player)[2], int i)
{
	if (*player[1] < (EXIT_AWAY - i))
		(*pos)[1] = (*player)[1] + (rand()
				% (ft_strlen(data->map[(*player)[0]]) - (*player)[1]));
	else
		(*pos)[1] = (*player)[1] - (rand() % ((*player)[1] + 1));
	if ((*player)[0] < (EXIT_AWAY - i))
		(*pos)[0] = (*player)[0] + (rand()
				% ((int)ft_ultimate_len(data->map) - (*player)[0]));
	else
		(*pos)[0] = (*player)[0] - (rand() % ((*player)[0] + 1));
}

static int	_spawn_exit2(t_data *data, int i)
{
	int		player[2];
	int		pos[2];
	char	**map_copy;

	player[1] = (int)floor(data->player.pos[1]);
	player[0] = (int)floor(data->player.pos[0]);
	if ((player[1] < (EXIT_AWAY - i) && ft_ultimate_len(data->map)
			< player[1] + (EXIT_AWAY - i))
		&& (player[0] < (EXIT_AWAY - i) && player[0] + (EXIT_AWAY - 1)
			> (int)ft_strlen(data->map[player[1]])))
		return (-1);
	_spawn_exit3(data, &pos, &player, i);
	if ((data->map[pos[0]][pos[1]] == '1' || data->map[pos[0]][pos[1]] == '2')
		&& (_available_ncell(data, pos)))
	{
		map_copy = ft_copy_tab(data->map);
		if (!map_copy)
			return (1);
		map_copy[pos[0]][pos[1]] = 'X';
		if (flood_fill(map_copy, 'X', player[1], player[0]))
			return (ft_free_split(map_copy),
				data->map[pos[0]][pos[1]] = 'X', 2);
		ft_free_split(map_copy);
	}
	return (0);
}

int	spawn_the_exit(t_data *data)
{
	int	i;
	int	res;

	res = 0;
	while (res != 2)
	{
		i = 0;
		while (i < EXIT_AWAY)
		{
			res = _spawn_exit2(data, i);
			if (res == 1)
				return (1);
			else if (res == 2)
				return (0);
			i++;
		}
	}
	return (1);
}
