/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:44:57 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/20 16:27:53 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	m_nodefree(t_data data, t_maps *map_node)
{
	if (!map_node)
		return ;
	if (map_node->name)
		free(map_node->name);
	if (map_node->path)
		free(map_node->path);
	if (map_node->preview && data.mlx)
		mlx_destroy_image(data.mlx, map_node->preview);
	free(map_node);
	map_node = NULL;
}

void	m_lstclear(t_data data, t_maps **lst_maps)
{
	t_maps	*tmp;

	while (*lst_maps)
	{
		tmp = (*lst_maps)->next;
		m_nodefree(data, *lst_maps);
		*lst_maps = tmp;
	}
}

void	d_lstclear(t_data data, t_doors *lst_doors)
{
	t_doors	*tmp;

	while (lst_doors)
	{
		tmp = lst_doors->next;
		if (lst_doors->img && data.mlx)
			mlx_destroy_image(data.mlx, lst_doors->img);
		free(lst_doors);
		lst_doors = tmp;
	}
}
