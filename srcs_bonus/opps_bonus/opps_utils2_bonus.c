/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opps_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:37:51 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:15:43 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

void	free_gengar(t_data *data)
{
	t_opps	*ops;
	t_opps	*next;

	ops = data->gengar;
	if (!ops)
		return ;
	while (ops)
	{
		next = ops->next;
		free(ops);
		ops = next;
	}
	return ;
}

void	opps_collide(t_opps *ops, t_data *data)
{
	int	pos[2];

	if (!ops)
		return ;
	pos[0] = (int)floor(ops->pos[0]);
	pos[1] = (int)floor(ops->pos[1]);
	_destroy_gengar(ops, data);
	data->map[pos[0]][pos[1]] = '0';
	data->player.hp--;
	data->nb_opps--;
	data->is_dmg = data->nloop;
	if (data->player.hp <= 0)
	{
		data->is_end = 2;
		_destroy_gengar(ops, data);
		menu_setup(data, 2);
	}
}

void	key_collide(int x, int y, t_data *data)
{
	data->player.keys = 1;
	data->map[y][x] = '0';
}

void	exit_collide(t_data *data)
{
	data->is_end = 1;
	menu_setup(data, 2);
}
