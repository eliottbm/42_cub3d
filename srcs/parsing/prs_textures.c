/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:59:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/12 14:30:28 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	create_imgs(t_data *data, char *path, int ntex)
{
	int		he;
	int		wi;

	he = 0;
	wi = 0;
	if (ntex == 0)
		data->tex.no = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	else if (ntex == 1)
		data->tex.so = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	else if (ntex == 2)
		data->tex.we = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	else if (ntex == 3)
		data->tex.ea = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	if ((he != TEX_SIZE || wi != TEX_SIZE)
		|| (ntex == 0 && !data->tex.no)
		|| (ntex == 1 && !data->tex.so)
		|| (ntex == 2 && !data->tex.we)
		|| (ntex == 3 && !data->tex.ea))
		return (1);
	return (0);
}

static void	rgb_to_hex(char **rgb, int *toset)
{
	if (!rgb)
		return ;
	if (!rgb[0] || !rgb[1] || !rgb[2] || !tab_iscolor(rgb))
	{
		ft_free_split(rgb);
		return ;
	}
	*toset = ((ft_atoi(rgb[0]) * 65536)
			+ (ft_atoi(rgb[1]) * 256)
			+ ft_atoi(rgb[2]));
	ft_free_split(rgb);
}

static int	is_texture_set(t_data *data, char *line)
{
	int			i;
	int			len;
	const char	*tests[] = {
		"NO ", "SO ", "WE ", "EA ", "F ", "C "
	};

	i = 0;
	while (i < 6)
	{
		len = ft_strlen((char *)tests[i]);
		if (!ft_strncmp(line, (char *)tests[i], len))
		{
			if ((i == 0 && data->tex.no)
				|| (i == 1 && data->tex.so)
				|| (i == 2 && data->tex.we)
				|| (i == 3 && data->tex.ea)
				|| (i == 4 && data->tex.f >= 0)
				|| (i == 5 && data->tex.c >= 0))
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	set_textures2(t_data *data, char *line, int ntex)
{
	char	*tmp;
	char	**rgb;

	if (isline_valid(line, ntex))
		return (1);
	rgb = NULL;
	tmp = strrmset(line, ' ');
	if (!tmp)
		return (1);
	if (ntex < 4 && (check_ext(tmp, ".xpm") || create_imgs(data, tmp, ntex)))
		return (free(tmp), 1);
	if (ntex >= 4)
	{
		rgb = ft_split(tmp, ',');
		if (ntex == 4)
			rgb_to_hex(rgb, &data->tex.f);
		else if (ntex == 5)
			rgb_to_hex(rgb, &data->tex.c);
		if ((ntex == 4 && data->tex.f < 0) || (ntex == 5 && data->tex.c < 0))
			return (free(tmp), 1);
	}
	free(tmp);
	return (0);
}

int	set_textures(t_data *data, char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = -1;
	while (line[i] == ' ')
		i++;
	check = is_texture_set(data, &line[i]);
	if (check == -1)
		return (1);
	else if (check < 4)
		i += 2;
	else
		i += 1;
	while (line[i] == ' ')
		i++;
	if (set_textures2(data, &line[i], check))
		return (1);
	return (0);
}
