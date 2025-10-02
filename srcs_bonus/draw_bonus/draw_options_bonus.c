/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_options_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:13:10 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/16 17:03:40 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	select_setup3(t_data *data, int option)
{
	if (option == PLAY)
	{
		data->imgl2.l2_dim[0] = data->menu.p_dim[0];
		data->imgl2.l2_dim[1] = data->menu.p_dim[1];
		data->imgl2.l2_pos[0] = data->menu.p_pos[0];
		data->imgl2.l2_pos[1] = data->menu.p_pos[1];
	}
	else if (option == QUIT)
	{
		data->imgl2.l2_dim[0] = data->menu.q_dim[0];
		data->imgl2.l2_dim[1] = data->menu.q_dim[1];
		data->imgl2.l2_pos[0] = data->menu.q_pos[0];
		data->imgl2.l2_pos[1] = data->menu.q_pos[1];
	}
	else if (option == RESUME)
	{
		data->imgl2.l2_dim[0] = data->menu.r_dim[0];
		data->imgl2.l2_dim[1] = data->menu.r_dim[1];
		data->imgl2.l2_pos[0] = data->menu.r_pos[0];
		data->imgl2.l2_pos[1] = data->menu.r_pos[1];
	}
}

static void	select_setup2(t_data *data, int option)
{
	if (option == MAIN)
	{
		data->imgl2.l2_dim[0] = data->menu.m_dim[0];
		data->imgl2.l2_dim[1] = data->menu.m_dim[1];
		if (data->is_end == 0)
		{
			data->imgl2.l2_pos[0] = data->menu.m_pos[0];
			data->imgl2.l2_pos[1] = data->menu.m_pos[1];
		}
		else
		{
			data->imgl2.l2_pos[0] = WIN_HEIGHT / 2;
			data->imgl2.l2_pos[1] = data->menu.m_pos[1];
		}
	}
	else
		select_setup3(data, option);
}

static void	*select_option(t_data *data, int option, int hover)
{
	if (option == RESUME && hover)
		return (data->tex.resume_h);
	else if (option == RESUME)
		return (data->tex.resume);
	else if (option == MAIN && hover)
		return (data->tex.main_h);
	else if (option == MAIN)
		return (data->tex.main);
	else if (option == PLAY && hover)
		return (data->tex.play_h);
	else if (option == PLAY)
		return (data->tex.play);
	else if (option == QUIT && hover)
		return (data->tex.quit_h);
	else if (option == QUIT)
		return (data->tex.quit);
	return (NULL);
}

void	opts_setup(t_data *data, int option, int hover)
{
	void	*imgtoput;
	int		tmp;
	t_l2	*imgl2;

	imgl2 = &data->imgl2;
	select_setup2(data, option);
	imgtoput = select_option(data, option, hover);
	imgl2->s_l2 = mlx_get_data_addr(
			imgtoput, &tmp, &imgl2->l2_size, &tmp);
	l2draw(data, 1);
	mlx_put_image_to_window(
		data->mlx, data->win, data->draw.i_world, 0, 0);
	sl2_init(&data->imgl2);
}
