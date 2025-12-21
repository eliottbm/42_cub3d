/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:27 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/29 14:44:22 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

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

int	encode_color(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	*trim_name(char *str)
{
	int		len;
	char	*trimed;
	int		shorted;

	shorted = 0;
	len = ft_strlen(str);
	while (len > 1 && str[len - 1] && str[len] != '.')
		len--;
	if (len >= 40)
	{
		len = 37;
		shorted = 1;
	}
	trimed = ft_strdup_till_i(str, len);
	if (!trimed)
		return (NULL);
	if (shorted)
		trimed = ft_strjoin_s1(trimed, "...");
	if (!trimed)
		return (NULL);
	return (trimed);
}
