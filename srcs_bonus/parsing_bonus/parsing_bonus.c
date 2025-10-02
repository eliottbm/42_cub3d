/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:05:30 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/01 17:48:58 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	make_map(t_data *data, int fd, char *line)
{
	char	*buf;
	int		i;
	int		check;

	i = -1;
	check = 0;
	buf = get_next_line(fd);
	while (buf)
	{
		line = ft_strjoin_s1(line, buf);
		if (!line)
			return (free(buf), 1);
		(free(buf), buf = get_next_line(fd));
	}
	while (line[++i])
	{
		if (!check && line[i] == '\n' && line[i + 1] && line[i + 1] == '\n')
			check = 1;
		else if (check == 1 && line[i] != '\n')
			return (free(line), 1);
	}
	data->map = ft_split(line, '\n');
	if (!data->map)
		return (free(line), 1);
	return (free(line), 0);
}

static int	read_beforemap(t_data *data, char *buf)
{
	int	i;

	i = 0;
	if (ft_strncmp(buf, "\n", 2) != 0 && data->tex.wall
		&& data->tex.ceil && data->tex.floor && data->tex.exit
		&& is_texture_set(data, buf, &i) == -1)
		return (1);
	return (0);
}

static int	read_file(t_data *data, int fd)
{
	char	*buf;
	char	*nl;

	buf = get_next_line(fd);
	while (buf)
	{
		if (read_beforemap(data, buf))
			return (make_map(data, fd, buf));
		else
		{
			nl = ft_strchr(buf, '\n');
			if (nl)
				(*nl = '\0');
			if (buf[0])
				if (set_textures(data, buf))
					return (free(buf), 1);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	return (0);
}

static void	rewrite_map(char **map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int	parsing(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_file(data, fd))
		return (close(fd), 1);
	close(fd);
	if (data->tex.doors && d_lstorder_check(data->tex.doors))
		return (1);
	if (data->tex.doors)
		data->tex.n_doors = d_lstsize(data->tex.doors);
	if (!data->map || !ismapvalid_chars(data, data->map))
		return (1);
	if (!ismapvalid_format(data))
		return (1);
	rewrite_map(data->map);
	return (0);
}
