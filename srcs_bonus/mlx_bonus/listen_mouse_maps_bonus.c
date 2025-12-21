/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_mouse_maps_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:32:41 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/22 15:55:18 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

static int	arrow_hover(int x, int y, t_draw draw)
{
	if (draw.s_arrow[(y * draw.arrowsize) + (x * 4) + 0] == 0
		&& draw.s_arrow[(y * draw.arrowsize) + (x * 4) + 1] == 0
		&& draw.s_arrow[(y * draw.arrowsize) + (x * 4) + 2] == 0)
		return (0);
	return (1);
}

static int	mouse_maps3(int x, int y, t_game *game, int i)
{
	if (x >= game->data.menu.mapspos[i][1]
		&& x <= game->data.menu.mapspos[i][1] + game->data.menu.mp_dim[1] + 40
		&& y >= game->data.menu.mapspos[i][0]
		&& y <= game->data.menu.mapspos[i][0] + game->data.menu.mp_dim[0] + 60)
	{
		game->data.menu.selected = i + 6;
		draw_previews_setup(game, i, 1);
		return (1);
	}
	else if (game->data.menu.selected == i + 6)
	{
		game->data.menu.selected = NONE;
		draw_previews_setup(game, i, 0);
		return (1);
	}
	return (0);
}

static void	mouse_maps2(int x, int y, t_game *game, int *hover)
{
	int	i;

	i = 0;
	while (i < game->nmaps)
	{
		if (*hover == 0)
			*hover = mouse_maps3(x, y, game, i);
		else
			mouse_maps3(x, y, game, i);
		i++;
	}
}

void	mouse_maps(int x, int y, t_game *game, t_menu menu)
{
	int	i;
	int	hover;

	i = 0;
	hover = 0;
	if ((x >= menu.sm_margin && x <= menu.sm_margin + menu.a_dim[1])
		&& (y >= menu.sm_margin && y <= menu.sm_margin + menu.a_dim[0])
		&& arrow_hover(x - menu.sm_margin, y - menu.sm_margin, game->data.draw))
	{
		game->data.menu.selected = BACK;
		draw_back_arrow(&game->data, 1);
		hover = 1;
	}
	else if (menu.selected == BACK)
	{
		game->data.menu.selected = NONE;
		draw_back_arrow(&game->data, 0);
		hover = 1;
	}
	else
		mouse_maps2(x, y, game, &hover);
	if (hover)
		while (i < 6)
			draw_texts_setup(game, i++);
}
