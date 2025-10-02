/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opps_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:32:47 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:26:39 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

t_opps	*_create_gengar(int (pos)[2])
{
	t_opps	*opps;

	opps = malloc(sizeof(t_opps));
	if (!opps)
		return (NULL);
	opps->next = NULL;
	opps->prev = NULL;
	opps->sprite = 0;
	opps->seen = 0;
	opps->last_m = -1;
	opps->pos[0] = pos[0] + 0.5;
	opps->pos[1] = pos[1] + 0.5;
	return (opps);
}

t_opps	*_get_last_gengar(t_data *data)
{
	t_opps	*tmp;

	tmp = data->gengar;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	add_gengar_back(t_data *data, int (pos)[2])
{
	t_opps	*new;
	t_opps	*last;

	new = _create_gengar(pos);
	if (!new)
		return (1);
	if (!data->gengar)
		return (data->gengar = new, 0);
	last = _get_last_gengar(data);
	if (!last)
		return (1);
	last->next = new;
	new->prev = last;
	new->last_m = -1;
	return (0);
}

t_opps	*_which_gengar(t_data *data, int x, int y)
{
	t_opps	*ops;

	ops = data->gengar;
	if (!ops)
		return (NULL);
	while (ops)
	{
		if ((int)floor(ops->pos[1]) == x
			&& (int)floor(ops->pos[0]) == y)
			return (ops);
		ops = ops->next;
	}
	return (NULL);
}

void	_destroy_gengar(t_opps *ops, t_data *data)
{
	t_opps	*next;
	t_opps	*prev;

	if (!ops)
		return ;
	if (ops == data->gengar)
	{
		data->gengar = ops->next;
		if (ops->next)
			ops->next->prev = NULL;
		free(ops);
		ops = NULL;
		return ;
	}
	next = ops->next;
	prev = ops->prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	if (ops)
		free(ops);
	ops = NULL;
	return ;
}
