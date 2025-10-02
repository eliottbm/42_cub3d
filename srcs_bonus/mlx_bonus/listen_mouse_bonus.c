/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:32:41 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:32 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static void	mouse_ingame(int x, t_data *data)
{
	if (x < WIN_WIDTH / 2)
		rotate_cam(data, 0);
	else if (x > WIN_WIDTH / 2)
		rotate_cam(data, 1);
}

static void	mouse_start(int x, int y, t_data *data, t_menu menu)
{
	if ((x >= menu.p_pos[1] && x <= menu.p_pos[1] + menu.p_dim[1])
		&& (y >= menu.p_pos[0] && y <= menu.p_pos[0] + menu.p_dim[0]))
	{
		data->menu.selected = PLAY;
		opts_setup(data, PLAY, 1);
	}
	else if (data->menu.selected == PLAY)
	{
		data->menu.selected = NONE;
		opts_setup(data, PLAY, 0);
	}
	if ((x >= menu.q_pos[1] && x <= menu.q_pos[1] + menu.q_dim[1])
		&& (y >= menu.q_pos[0] && y <= menu.q_pos[0] + menu.q_dim[0]))
	{
		data->menu.selected = QUIT;
		opts_setup(data, QUIT, 1);
	}
	else if (data->menu.selected == QUIT)
	{
		data->menu.selected = NONE;
		opts_setup(data, QUIT, 0);
	}
}

static void	mouse_pause(int x, int y, t_data *data, t_menu menu)
{
	if ((x >= menu.r_pos[1] && x <= menu.r_pos[1] + menu.r_dim[1])
		&& (y >= menu.r_pos[0] && y <= menu.r_pos[0] + menu.r_dim[0]))
	{
		data->menu.selected = RESUME;
		opts_setup(data, RESUME, 1);
	}
	else if (menu.selected == RESUME)
	{
		data->menu.selected = NONE;
		opts_setup(data, RESUME, 0);
	}
	if ((x >= menu.m_pos[1] && x <= menu.m_pos[1] + menu.m_dim[1])
		&& (y >= menu.m_pos[0] && y <= menu.m_pos[0] + menu.m_dim[0]))
	{
		data->menu.selected = MAIN;
		opts_setup(data, MAIN, 1);
	}
	else if (menu.selected == MAIN)
	{
		data->menu.selected = NONE;
		opts_setup(data, MAIN, 0);
	}
}

static void	mouse_end(int x, int y, t_data *data, t_menu menu)
{
	if ((x >= menu.m_pos[1] && x <= menu.m_pos[1] + menu.m_dim[1])
		&& (y >= WIN_HEIGHT / 2 && y <= WIN_HEIGHT / 2 + menu.m_dim[0]))
	{
		data->menu.selected = MAIN;
		opts_setup(data, MAIN, 1);
	}
	else if (menu.selected == MAIN)
	{
		data->menu.selected = NONE;
		opts_setup(data, MAIN, 0);
	}
}

int	listen_mouse(int x, int y, t_game *game)
{
	if (!game->data.menu.ispaused)
		mouse_ingame(x, &game->data);
	else if (game->data.menu.ispaused == 3 && game->data.is_end == 0)
		mouse_pause(x, y, &game->data, game->data.menu);
	else if (game->data.menu.ispaused == 3 && game->data.is_end != 0)
		mouse_end(x, y, &game->data, game->data.menu);
	else if (game->data.menu.ispaused == 1)
		mouse_start(x, y, &game->data, game->data.menu);
	else if (game->data.menu.ispaused == 5)
		mouse_maps(x, y, game, game->data.menu);
	return (0);
}
