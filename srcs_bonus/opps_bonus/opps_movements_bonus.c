/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opps_movements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:14:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/20 16:29:56 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	opps_step_ws(t_opps *ops, t_data *data, int way)
{
	int				pos[2];
	const double	speed = O_SPEED * data->player.m_speed;
	int				poso[2];
	char			c;

	poso[0] = (int)floor(ops->pos[0]);
	poso[1] = (int)floor(ops->pos[1]);
	pos[0] = poso[0];
	pos[1] = (int)floor(ops->pos[1] + (way * speed));
	if (!correct_pos(data->map, pos[0], pos[1])
		|| stay_away_fw(data, 1, way, ops))
		return (0);
	if (pos[1] == poso[1])
		return (ops->pos[1] += (way * speed), 1);
	c = data->map[pos[0]][pos[1]];
	if (c == '1' || c == 'X' || c == '2' || c == 'K' || c == 'G')
		return (0);
	if (pos[0] == (int)floor(data->player.pos[0])
		&& pos[1] == (int)floor(data->player.pos[1]))
		return (data->map[poso[0]][poso[1]] = '0', opps_collide(ops, data), 1);
	if (c == '0')
		return (ops->pos[1] += (way * speed),
			data->map[poso[0]][poso[1]] = '0',
			data->map[pos[0]][pos[1]] = 'G', 1);
	return (0);
}

static int	opps_step_ad(t_opps *ops, t_data *data, int way)
{
	int				pos[2];
	const double	speed = O_SPEED * data->player.m_speed;
	int				poso[2];
	char			c;

	poso[0] = (int)floor(ops->pos[0]);
	poso[1] = (int)floor(ops->pos[1]);
	pos[0] = (int)floor(ops->pos[0] + (way * speed));
	pos[1] = poso[1];
	if (!correct_pos(data->map, pos[0], pos[1])
		|| stay_away_fw(data, 0, way, ops))
		return (0);
	if (pos[0] == poso[0] && pos[1] == poso[1])
		return (ops->pos[0] += (way * speed), 1);
	c = data->map[pos[0]][pos[1]];
	if (c == '1' || c == 'X' || c == '2' || c == 'K' || c == 'G')
		return (0);
	if (pos[0] == (int)floor(data->player.pos[0])
		&& pos[1] == (int)floor(data->player.pos[1]))
		return (data->map[poso[0]][poso[1]] = '0', opps_collide(ops, data), 1);
	if (c == '0')
		return (ops->pos[0] += (way * speed),
			data->map[poso[0]][poso[1]] = '0',
			data->map[pos[0]][pos[1]] = 'G', 1);
	return (0);
}

static void	_opps_follow_player(t_opps *ops, t_data *data)
{
	double	pos[2];
	double	p_pos[2];
	double	dif[2];

	pos[1] = ops->pos[1];
	pos[0] = ops->pos[0];
	p_pos[1] = data->player.pos[1];
	p_pos[0] = data->player.pos[0];
	dif[0] = pos[0] - p_pos[0];
	dif[1] = pos[1] - p_pos[1];
	if (fabs(dif[0]) <= fabs(dif[1]))
	{
		if (dif[1] <= 0)
			opps_step_ws(ops, data, -1);
		else
			opps_step_ws(ops, data, 1);
	}
	else if (dif[0] <= 0)
		opps_step_ad(ops, data, -1);
	else
		opps_step_ad(ops, data, 1);
	if (ops)
		ops->seen = 0;
}

static int	_opps_movements_each(t_opps *ops, t_data *data)
{
	int	rd;
	int	i;

	i = 0;
	if (!ops)
		return (1);
	if (ops->seen == 1)
		return (_opps_follow_player(ops, data), 0);
	rd = rand() % (3 + 1);
	if (rd == 0 && 1 != ops->last_m)
		while (i++ < 5)
			opps_step_ws(ops, data, 1);
	else if (rd == 1 && 0 != ops->last_m)
		while (i++ < 5)
			opps_step_ws(ops, data, -1);
	else if (rd == 2 && 3 != ops->last_m)
		while (i++ < 5)
			opps_step_ad(ops, data, -1);
	else if (rd == 3 && 2 != ops->last_m)
		while (i++ < 5)
			opps_step_ad(ops, data, 1);
	ops->last_m = rd;
	return (0);
}

void	_opps_movements(t_data *data)
{
	t_opps	*ops;
	t_opps	*next;

	ops = data->gengar;
	if (!ops)
		return ;
	while (ops)
	{
		next = ops->next;
		_opps_movements_each(ops, data);
		if (ops)
			ops->seen = 0;
		if (next)
			ops = next;
		else
			ops = NULL;
	}
	return ;
}
