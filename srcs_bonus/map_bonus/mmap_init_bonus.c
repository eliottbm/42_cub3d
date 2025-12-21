/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:08:32 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/19 17:47:01 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

char	**create_tab(int x, int y)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (x + 1));
	if (!map)
		return (NULL);
	while (i < x)
	{
		map[i] = malloc(sizeof(char) * (y + 1));
		if (!map[i])
		{
			while (i >= 0)
			{
				free(map[i]);
				i--;
			}
			free(map);
			return (NULL);
		}
		map[i][y] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

static int	_init_map_init(char ***map, t_nk *v)
{
	*map = create_tab(5, 5);
	if (!*map)
		return (1);
	v->i = -1;
	return (0);
}

char	**_init_map(t_data *data)
{
	char	**m;
	int		p_pos[2];
	t_nk	v;

	if (_init_map_init(&m, &v))
		return (NULL);
	p_pos[0] = (int)floor(data->player.pos[0]);
	p_pos[1] = (int)floor(data->player.pos[1]);
	while (++v.i < 5)
	{
		v.j = -1;
		while (++v.j < 5)
		{
			if ((p_pos[0] - 2 + v.i) < 0
				|| (p_pos[0] - 2 + v.i) >= ft_ultimate_len(data->map)
				|| (p_pos[1] - 2 + v.j) < 0 || (size_t)(p_pos[1] - 2 + v.j)
				>= ft_strlen(data->map[p_pos[0] - 2 + v.i]))
				m[v.i][v.j] = '-';
			else if (v.j == 2 && v.i == 2)
				m[v.i][v.j] = 'P';
			else
				m[v.i][v.j] = data->map[p_pos[0] - 2 + v.i][p_pos[1] - 2 + v.j];
		}
	}
	return (m);
}

int	minimap(t_data *data)
{
	char	**map;

	if (data->is_end != 0)
		return (0);
	map = _init_map(data);
	if (!map)
	{
		end_mlx(data);
		return (1);
	}
	if (_mmap_draw(data, map))
	{
		ft_free_split(map);
		return (1);
	}
	ft_free_split(map);
	return (0);
}
