/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:03 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/15 18:04:22 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static int	err_return(t_data data)
{
	ft_puterror("Error\n");
	free_data(data);
	return (1);
}

static int	data_init(t_data *data)
{
	data->draw.i_world = NULL;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->tex.ea = NULL;
	data->tex.f = -1;
	data->tex.c = -1;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	return (0);
}

static int	winimg_init(t_data *data)
{
	int	tmp;

	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		return (1);
	data->draw.i_world = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->draw.i_world)
		return (1);
	data->draw.s_world = mlx_get_data_addr(data->draw.i_world, &tmp,
			&data->draw.worldsize, &data->draw.worldend);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if (data_init(&data))
		return (err_return(data));
	if (parsing(&data, av[1]))
		return (err_return(data));
	if (winimg_init(&data))
		return (err_return(data));
	raycast(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, listen_inputs, &data);
	mlx_hook(data.win, 17, 0, end_mlx, &data);
	mlx_loop(data.mlx);
	free_data(data);
	return (0);
}
