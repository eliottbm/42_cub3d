/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_inits_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:31:02 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/18 17:09:05 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	get_keypos(t_data *data, t_sprites *sprites)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'K')
			{
				sprites->sp_pos[0] = y + 0.5;
				sprites->sp_pos[1] = x + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	keysprite_init(t_data *data)
{
	int	j;
	int	tmp;

	j = -1;
	data->sprites[0].sp_k_or_g = 'K';
	data->sprites[0].sp_isview = 0;
	data->sprites[0].sp_dist = -1.0;
	data->sprites[0].sp_g_s_img[0] = NULL;
	data->sprites[0].sp_s_img = NULL;
	data->sprites[0].sp_hdiv = 6;
	data->sprites[0].sp_wdiv = 6;
	get_keypos(data, &data->sprites[0]);
	while (++j < 4)
		data->sprites[0].sp_k_s_img[j] = mlx_get_data_addr(
				data->tex.key[j], &tmp, &tmp, &tmp);
}

static int	oppsprite_init(t_data *data)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (++i < OPPS_NBR + 1)
	{
		j = -1;
		data->sprites[i].sp_k_or_g = 'G';
		data->sprites[i].sp_isview = 0;
		data->sprites[i].sp_dist = -1.0;
		data->sprites[i].sp_k_s_img[0] = NULL;
		data->sprites[i].sp_s_img = NULL;
		data->sprites[i].sp_hdiv = 1;
		data->sprites[i].sp_wdiv = 1;
		data->sprites[i].sp_hpos = 64.0;
		while (++j < 20)
			data->sprites[i].sp_g_s_img[j] = mlx_get_data_addr(
					data->tex.geng[j], &tmp, &tmp, &tmp);
	}
	return (0);
}

int	play_init(t_game *game)
{
	if (spawn_exit_keys(&game->data))
		return (1);
	keysprite_init(&game->data);
	oppsprite_init(&game->data);
	return (0);
}
