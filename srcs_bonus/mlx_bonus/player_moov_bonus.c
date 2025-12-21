/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moov_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:36:16 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/19 15:57:03 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static inline void	init_ws(int keycode, double *p_speed, t_data *data, int *y)
{
	*p_speed = data->player.m_speed;
	if (keycode == W_KEYCODE)
		*p_speed = -*p_speed;
	*y = (int)floor(data->player.pos[0]);
}

void	moov_player_ws(int keycode, t_data *data)
{
	int		x;
	int		y;
	double	p_speed;
	char	c;

	init_ws(keycode, &p_speed, data, &y);
	x = (int)floor(data->player.pos[1] + (data->player.dir[1] * p_speed));
	if (is_cellav(data, x, y))
		data->player.pos[1] += data->player.dir[1] * p_speed;
	x = (int)floor(data->player.pos[1]);
	y = (int)floor(data->player.pos[0] + (data->player.dir[0] * p_speed));
	if (is_cellav(data, x, y))
		data->player.pos[0] += data->player.dir[0] * p_speed;
	c = data->map[(int)floor(data->player.pos[0])]
	[(int)floor(data->player.pos[1])];
	if (c == 'X')
		exit_collide(data);
	else if (c == 'G')
		return (data->map[(int)floor(data->player.pos[0])]
			[(int)floor(data->player.pos[1])] = '0',
			opps_collide(_which_gengar(data, (int)floor(data->player.pos[1]),
					(int)floor(data->player.pos[0])), data), (void)1);
	else if (c == 'K')
		key_collide((int)floor(data->player.pos[1]),
			(int)floor(data->player.pos[0]), data);
}

static inline void	init_1line(t_data *data
	, int keycode, double *p_speed, double (*perp)[2])
{
	*p_speed = data->player.m_speed;
	if (keycode == A_KEYCODE)
		*p_speed = -(*p_speed);
	(*perp)[1] = data->player.dir[0];
	(*perp)[0] = -data->player.dir[1];
}

void	moov_player_ad(int keycode, t_data *data)
{
	int		pos[2];
	double	perp[2];
	double	p_speed;
	char	c;

	init_1line(data, keycode, &p_speed, &perp);
	pos[1] = (int)floor((data->player.pos[1]));
	pos[0] = (int)floor(data->player.pos[0] + (perp[0] * p_speed));
	if (is_cellav(data, pos[1], pos[0]))
		data->player.pos[0] += perp[0] * p_speed;
	pos[1] = (int)floor(data->player.pos[1] + (perp[1] * p_speed));
	pos[0] = (int)floor(data->player.pos[0]);
	if (is_cellav(data, pos[1], pos[0]))
		data->player.pos[1] += perp[1] * p_speed;
	c = data->map[(int)floor(data->player.pos[0])]
	[(int)floor(data->player.pos[1])];
	if (c == 'G')
		return (data->map[(int)floor(data->player.pos[0])]
			[(int)floor(data->player.pos[1])] = '0',
			opps_collide(_which_gengar(data, (int)floor(data->player.pos[1]),
					(int)floor(data->player.pos[0])), data), (void)1);
	else if (c == 'K')
		return (key_collide(pos[1], pos[0], data));
	else if (c == 'X')
		return (exit_collide(data));
}

void	rotate_cam(t_data *data, int rotatedir)
{
	double	x;
	double	y;
	double	r;

	r = data->player.m_rota;
	if (rotatedir)
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
