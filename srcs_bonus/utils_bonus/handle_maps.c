/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:41:57 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/10 17:24:08 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	gen_preview(t_data *data, t_maps *map_node)
{
	int		tmp;
	int		size;
	char	*s_preview;

	raycast(data, 1);
	map_node->preview = mlx_new_image(data->mlx,
			data->menu.mp_dim[1], data->menu.mp_dim[0]);
	if (!map_node->preview)
		return (1);
	s_preview = mlx_get_data_addr(map_node->preview, &tmp, &size, &tmp);
	data->imgl2.s_l2 = data->draw.s_world;
	data->imgl2.l2_size = data->draw.worldsize;
	data->imgl2.l2_pos[1] = data->menu.mp_dim[1];
	data->imgl2.l2_pos[0] = data->menu.mp_dim[0];
	data->imgl2.l2_scale[1] = (
			(double)data->imgl2.l2_pos[1]) / (double)WIN_WIDTH;
	data->imgl2.l2_scale[0] = (
			(double)data->imgl2.l2_pos[0]) / (double)WIN_HEIGHT;
	draw_resize(data, s_preview, size, 0);
	return (0);
}

static int	add_map(t_game *game, struct dirent *entry, char *dir)
{
	t_maps	*map_node;
	char	*path;
	char	*name;

	if (ft_strlen(entry->d_name) < 5 || check_ext(entry->d_name, ".cub"))
		return (0);
	path = ft_strjoin_c(dir, entry->d_name, '/');
	if (!path)
		return (0);
	if (parsing(&game->data, path))
		return (free(path), 0);
	name = trim_name(entry->d_name);
	if (!name)
		return (free(path), 0);
	map_node = m_lstnew(name, path);
	if (!map_node)
		return (free(name), free(path), 0);
	if (gen_preview(&game->data, map_node))
		return (m_nodefree(game->data, map_node), 0);
	m_lstadd_back(&game->maps, map_node);
	return (0);
}

int	read_maps(t_game *game)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(game->mdir);
	if (!dp)
		return (1);
	entry = readdir(dp);
	while (entry && (!game->maps || (game->maps && game->nmaps < 6)))
	{
		if (entry->d_type == 8)
		{
			add_map(game, entry, game->mdir);
			game->nmaps = m_lstsize(game->maps);
			free_data(game->data);
			data_init(&game->data);
		}
		entry = readdir(dp);
	}
	return (closedir(dp), 0);
}
