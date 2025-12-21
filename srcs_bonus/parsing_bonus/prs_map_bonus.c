/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:01:16 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/10 17:49:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	ismapvalid_chars(t_data *data, char **map)
{
	int	y;
	int	x;
	int	count;

	y = -1;
	count = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			if ((map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' '
				&& map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != 'W' && (map[y][x] != '2'
				&& !data->tex.wall2) && (map[y][x] != 'D'
				&& !data->tex.doors)) || count > 1)
				return (0);
		}
	}
	if (!count)
		return (0);
	return (1);
}

static void	save_playerdata2(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player.fov[0] = FOV_DEG / 100.00;
		data->player.fov[1] = 0;
		data->player.dir[0] = 0;
		data->player.dir[1] = 1;
	}
	else if (c == 'W')
	{
		data->player.fov[0] = -(FOV_DEG / 100.00);
		data->player.fov[1] = 0;
		data->player.dir[0] = 0;
		data->player.dir[1] = -1;
	}
}

static void	save_playerdata(t_data *data, char c, size_t y, size_t x)
{
	if (c == 'N')
	{
		data->player.fov[0] = 0;
		data->player.fov[1] = FOV_DEG / 100.00;
		data->player.dir[0] = -1;
		data->player.dir[1] = 0;
	}
	else if (c == 'S')
	{
		data->player.fov[0] = 0;
		data->player.fov[1] = -(FOV_DEG / 100.00);
		data->player.dir[0] = 1;
		data->player.dir[1] = 0;
	}
	else
		save_playerdata2(data, c);
	data->player.pos[0] = y + 0.5;
	data->player.pos[1] = x + 0.5;
	data->player.hp = PLAYER_HEALTH;
	data->player.keys = 0;
	data->player.m_speed = (data->player.m_rota = 0);
}

int	ismapvalid_format(t_data *data)
{
	size_t	y;
	size_t	x;
	char	c;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (validmap_checks(data->map, c, y, x))
				return (0);
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
				save_playerdata(data, c, y, x);
			x++;
		}
		y++;
	}
	data->h_map = y;
	return (1);
}
