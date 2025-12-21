/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_textures_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:59:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/30 15:23:32 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	is_texture_set2(t_data *data, int i)
{
	if ((i == 0 && data->tex.wall)
		|| (i == 1 && data->tex.ceil)
		|| (i == 2 && data->tex.floor)
		|| (i == 3 && data->tex.wall2)
		|| (i == 4 && data->tex.exit))
		return (1);
	return (0);
}

static int	is_door_set2(t_doors *doors, size_t ndoor)
{
	while (doors)
	{
		if (doors->n == ndoor)
			return (1);
		doors = doors->next;
	}
	return (0);
}

static int	is_door_set(t_data *data, char *line, int *i)
{
	int	ndoor;

	ndoor = ft_atoi(&line[*i + 1]);
	if (ndoor < 0 || ndoor > 12)
		return (-1);
	if (data->tex.doors && is_door_set2(data->tex.doors, ndoor))
		return (-2);
	while (line[*i] != ' ')
		*i += 1;
	return (ndoor + 4);
}

int	is_texture_set(t_data *data, char *line, int *i)
{
	int			j;
	int			len;
	const char	*tests[] = {
		"W ", "C ", "F ", "W2 ", "E "
	};

	j = 0;
	while (line[*i] == ' ')
		*i += 1;
	if (line[*i] == 'D' && line[*i + 1])
		return (is_door_set(data, line, i));
	while (j < 5)
	{
		len = ft_strlen((char *)tests[j]);
		if (!ft_strncmp(line, (char *)tests[j], len))
		{
			if (is_texture_set2(data, j))
				return (-2);
			return ((*i += len), j);
		}
		j++;
	}
	return (-1);
}
