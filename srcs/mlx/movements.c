/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:25:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/15 15:45:07 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	moov_player_ws(int keycode, t_data *data)
{
	int		x;
	int		y;
	double	p_speed;

	p_speed = data->player.m_speed;
	if (keycode == W_KEYCODE)
		p_speed = -p_speed;
	x = (int)floor((data->player.pos[1] + (data->player.dir[1] * p_speed)));
	y = (int)floor(data->player.pos[0]);
	if (ft_strlen(data->map[y]) < (size_t)x)
		return ;
	if (data->map[y][x] && data->map[y][x] == '0')
		data->player.pos[1] += data->player.dir[1] * p_speed;
	x = (int)(data->player.pos[1]);
	y = (int)(data->player.pos[0] + (data->player.dir[0] * p_speed));
	if (ft_strlen(data->map[y]) < (size_t)x)
		return ;
	if (data->map[y][x] && data->map[y][x] == '0')
		data->player.pos[0] += data->player.dir[0] * p_speed;
	return ;
}

void	moov_player_ad(int keycode, t_data *data)
{
	int		x;
	int		y;
	double	perp[2];
	double	p_speed;

	perp[1] = data->player.dir[0];
	perp[0] = -data->player.dir[1];
	p_speed = data->player.m_speed;
	if (keycode == A_KEYCODE)
		p_speed = -p_speed;
	x = (int)floor((data->player.pos[1]));
	y = (int)floor(data->player.pos[0] + (perp[0] * p_speed));
	if (data->map[y][x] && data->map[y][x] == '0')
		data->player.pos[0] += perp[0] * p_speed;
	x = (int)(data->player.pos[1] + (perp[1] * p_speed));
	y = (int)(data->player.pos[0]);
	if (ft_strlen(data->map[y]) < (size_t)x)
		return ;
	if (data->map[y][x] && data->map[y][x] == '0')
		data->player.pos[1] += perp[1] * p_speed;
	return ;
}
