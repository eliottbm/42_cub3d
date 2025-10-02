/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:16:45 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/15 13:44:49 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	free_tex(t_data data)
{
	t_tex	tex;

	tex = data.tex;
	if (tex.no)
		mlx_destroy_image(data.mlx, tex.no);
	if (tex.so)
		mlx_destroy_image(data.mlx, tex.so);
	if (tex.we)
		mlx_destroy_image(data.mlx, tex.we);
	if (tex.ea)
		mlx_destroy_image(data.mlx, tex.ea);
}

void	free_data(t_data data)
{
	free_tex(data);
	if (data.draw.i_world)
		mlx_destroy_image(data.mlx, data.draw.i_world);
	if (data.map)
		ft_free_split(data.map);
	if (data.win)
		mlx_destroy_window(data.mlx, data.win);
	if (data.mlx)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
	}
}
