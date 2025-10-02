/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_textures_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:59:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/30 15:24:19 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	create_imgs2(t_data *data, char *path, int ntex)
{
	int	he;
	int	wi;
	int	tmp;

	he = 0;
	wi = 0;
	if (ntex == 2)
	{
		data->tex.floor = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
		data->draw.s_floor = (mlx_get_data_addr(data->tex.floor,
					&tmp, &tmp, &tmp));
	}
	else if (ntex == 3)
		data->tex.wall2 = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	else if (ntex == 4)
		data->tex.exit = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	if (he != TEX_SIZE || wi != TEX_SIZE)
		return (1);
	return (0);
}

static int	create_doors(t_data *data, char *path, int ntex)
{
	int		he;
	int		wi;
	t_doors	*newdoor;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	if (!img || he != TEX_SIZE || wi != TEX_SIZE)
		return (1);
	newdoor = d_lstnew(img, ntex - 4);
	if (!newdoor)
	{
		mlx_destroy_image(data->mlx, img);
		return (1);
	}
	d_lstadd_sort(&data->tex.doors, newdoor);
	return (0);
}

static int	create_imgs(t_data *data, char *path, int ntex)
{
	int	he;
	int	wi;
	int	tmp;

	he = 0;
	wi = 0;
	if (ntex == 0)
		data->tex.wall = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
	else if (ntex == 1)
	{
		data->tex.ceil = mlx_xpm_file_to_image(data->mlx, path, &wi, &he);
		data->draw.s_ceil = (mlx_get_data_addr(data->tex.ceil,
					&tmp, &tmp, &tmp));
	}
	else if (ntex < 5 && create_imgs2(data, path, ntex))
		return (1);
	else if (ntex > 4 && create_doors(data, path, ntex))
		return (1);
	if ((ntex < 2 && (he != TEX_SIZE || wi != TEX_SIZE))
		|| (ntex == 0 && !data->tex.wall) || (ntex == 1 && !data->tex.ceil)
		|| (ntex == 2 && !data->tex.floor) || (ntex == 3 && !data->tex.wall2)
		|| (ntex == 4 && !data->tex.exit))
		return (1);
	return (0);
}

int	set_textures(t_data *data, char *line)
{
	int		i;
	int		ntex;
	char	*tmp;

	i = 0;
	ntex = -1;
	ntex = is_texture_set(data, &line[i], &i);
	if (ntex < 0)
		return (1);
	while (line[i] == ' ')
		i++;
	if (isline_valid(&line[i]))
		return (1);
	tmp = strrmset(&line[i], ' ');
	if (!tmp)
		return (1);
	if (check_ext(tmp, ".xpm") || create_imgs(data, tmp, ntex))
		return (free(tmp), 1);
	return (free(tmp), 0);
}
