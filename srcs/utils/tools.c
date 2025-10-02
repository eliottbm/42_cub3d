/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:27 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/06 15:55:06 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	calc_fps(t_data *data)
{
	data->ray.e_time = data->ray.b_time;
	data->ray.b_time = (double)get_current_time();
	data->ray.fps = (data->ray.e_time - data->ray.b_time) / 1000.0;
	data->player.m_speed = data->ray.fps * (double)MOOVE_SPEED;
	data->player.m_rota = data->ray.fps * (double)ROTATE_SPEED;
}
