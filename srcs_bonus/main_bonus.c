/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:03 by ebengtss          #+#    #+#             */
/*   Updated: 2024/12/19 17:43:49 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs_bonus/cub3d_bonus.h"

int	end_mlx(t_data *data)
{
	return (mlx_loop_end(data->mlx), 0);
}

static int	err_return(t_game game)
{
	ft_puterror("Error\n");
	free_game(game);
	return (1);
}

static int	main_loop(t_data *data)
{
	if (data->menu.ispaused == 0)
	{
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		raycast(data, 0);
		opps_main(data);
		calc_fps(data);
		if (minimap(data))
			return (end_mlx(data), 1);
		mlx_put_image_to_window(
			data->mlx, data->win, data->draw.i_world, 0, 0);
		if (data->nloop == 40)
			data->loopback = 1;
		else if (data->nloop == 1)
			data->loopback = 0;
		if (!data->loopback)
			data->nloop += 1;
		else
			data->nloop -= 1;
	}
	usleep(16);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
	srand(time(NULL));
	if (game_init(&game, av[1]))
		return (err_return(game));
	menu_setup(&game.data, 0);
	mlx_hook(game.data.win, KeyPress, KeyPressMask, listen_keys, &game.data);
	mlx_hook(game.data.win, MotionNotify,
		PointerMotionMask, listen_mouse, &game);
	mlx_hook(game.data.win, 4, ButtonPressMask, listen_clicks, &game);
	mlx_hook(game.data.win, 17, 0, end_mlx, &game.data);
	mlx_loop_hook(game.data.mlx, main_loop, &game.data);
	mlx_loop(game.data.mlx);
	return (free_game(game), 0);
}
