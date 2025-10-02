/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:41:57 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/29 13:03:38 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	is_lookdoor(t_data *data)
{
	return (data->ray.pos[0] == data->d_anim.da_doorpos[0]
		&& data->ray.pos[1] == data->d_anim.da_doorpos[1]);
}

static int	is_neardoor(t_data *data)
{
	if ((((int)data->player.pos[0] == data->d_anim.da_doorpos[0] - 1
				|| (int)data->player.pos[0] == data->d_anim.da_doorpos[0] + 1)
			&& (int)data->player.pos[1] == data->d_anim.da_doorpos[1])
		|| (((int)data->player.pos[1] == data->d_anim.da_doorpos[1] - 1
				|| (int)data->player.pos[1] == data->d_anim.da_doorpos[1] + 1)
			&& (int)data->player.pos[0] == data->d_anim.da_doorpos[0]))
		return (1);
	return (0);
}

static void	handle_doors2(t_data *data)
{
	if (data->d_anim.da_isrun != 0)
	{
		if (data->d_anim.da_isdone)
			data->d_anim.da_isdone = 0;
		data->d_anim.da_isrun = 2;
		if (data->d_anim.da_frame == 1)
			d_anim_init(data);
		else
		{
			if (data->nloop % DOOR_SPEED == 0)
				data->d_anim.da_frame -= 1;
			data->d_anim.da_img = get_ndoor_img(
					data->tex.doors, data->d_anim.da_frame);
		}
	}
}

int	handle_doors(t_data *data)
{
	if (data->d_anim.da_isdone
		&& (int)data->player.pos[0] == data->d_anim.da_doorpos[0]
		&& (int)data->player.pos[1] == data->d_anim.da_doorpos[1])
		return (0);
	ray_update(&data->ray, data->player, WIN_WIDTH / 2);
	ray_step(&data->ray, data->player);
	run_dda(data, &data->ray, data->map, 0);
	if (!data->d_anim.da_check)
		return (handle_doors2(data), 0);
	ray_hit(&data->ray, data->player);
	if (data->d_anim.da_isrun == 0)
	{
		data->d_anim.da_doorpos[0] = data->ray.pos[0];
		data->d_anim.da_doorpos[1] = data->ray.pos[1];
	}
	if (!is_neardoor(data) || !is_lookdoor(data))
		return (handle_doors2(data), 0);
	data->d_anim.da_isrun = 1;
	if (data->d_anim.da_frame == data->tex.n_doors)
		data->d_anim.da_isdone = 1;
	else if (data->nloop % DOOR_SPEED == 0)
		data->d_anim.da_frame += 1;
	data->d_anim.da_img = get_ndoor_img(data->tex.doors, data->d_anim.da_frame);
	return (0);
}
