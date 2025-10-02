/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_inputs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:25:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/11 13:55:45 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	listen_keys(int keycode, t_data *data)
{
	if (data->menu.ispaused == 1 || data->menu.ispaused == 5)
	{
		if (keycode == ESC_KEYCODE)
			end_mlx(data);
		else
			return (0);
	}
	if (keycode == ESC_KEYCODE)
		menu_setup(data, 2);
	else if (data->menu.ispaused != 0)
		return (0);
	else if (keycode == W_KEYCODE || keycode == S_KEYCODE)
		(moov_player_ws(keycode, data));
	else if (keycode == A_KEYCODE || keycode == D_KEYCODE)
		(moov_player_ad(keycode, data));
	return (0);
}

static int	start_map(t_game *game)
{
	t_maps	*maps;
	int		i;

	i = 0;
	game->data.menu.ispaused = 9;
	maps = game->maps;
	while (maps && i != game->data.menu.selected - 6)
	{
		maps = maps->next;
		i++;
	}
	free_data(game->data);
	data_init(&game->data);
	if (parsing(&game->data, maps->path))
	{
		load_reset(game);
		if (read_maps(game))
			return (1);
		return (draw_map_select(game), 0);
	}
	if (play_init(game))
		return (1);
	resume_game(&game->data);
	return (0);
}

int	listen_clicks(int click, int x, int y, t_game *game)
{
	const t_menu	menu = game->data.menu;

	(void)x;
	(void)y;
	if (click != 1 || !menu.ispaused)
		return (0);
	if (menu.ispaused == 3 && menu.selected == RESUME)
		resume_game(&game->data);
	else if ((menu.ispaused == 3 && menu.selected == MAIN)
		|| (menu.ispaused == 5 && menu.selected == BACK))
		(load_reset(game), menu_setup(&game->data, 0));
	else if (menu.ispaused == 1 && menu.selected == PLAY)
	{
		if (read_maps(game))
			end_mlx(&game->data);
		draw_map_select(game);
	}
	else if (menu.ispaused == 1 && menu.selected == QUIT)
		end_mlx(&game->data);
	else if (menu.ispaused == 5 && menu.selected > 5)
		if (start_map(game))
			end_mlx(&game->data);
	return (0);
}
