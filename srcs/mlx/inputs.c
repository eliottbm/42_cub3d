/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:32:41 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/12 16:49:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	end_mlx(t_data *data)
{
	return (mlx_loop_end(data->mlx), 0);
}

static void	rotate_cam(int keycode, t_data *data)
{
	double	x;
	double	y;
	double	r;

	r = data->player.m_rota;
	if (keycode == RGT_KEYCODE)
		r = -r;
	x = data->player.dir[1];
	y = data->player.dir[0];
	data->player.dir[1] = (x * cos(r)) - (y * sin(r));
	data->player.dir[0] = (x * sin(r)) + (y * cos(r));
	x = data->player.fov[1];
	y = data->player.fov[0];
	data->player.fov[1] = (x * cos(r)) - (y * sin(r));
	data->player.fov[0] = (x * sin(r)) + (y * cos(r));
}

int	listen_inputs(int keycode, t_data *data)
{
	if (keycode == ESC_KEYCODE)
		return (end_mlx(data));
	if (keycode == LFT_KEYCODE || keycode == RGT_KEYCODE)
		(rotate_cam(keycode, data), raycast(data));
	if (keycode == W_KEYCODE || keycode == S_KEYCODE)
		(moov_player_ws(keycode, data), raycast(data));
	else if (keycode == A_KEYCODE || keycode == D_KEYCODE)
		(moov_player_ad(keycode, data), raycast(data));
	return (0);
}
