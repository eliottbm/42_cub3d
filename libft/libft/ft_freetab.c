/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:01:19 by mtrullar          #+#    #+#             */
/*   Updated: 2024/12/01 15:42:58 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_freetab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**ft_copy_tab(char **map)
{
	char	**result;
	int		i;
	int		len;

	len = ft_ultimate_len(map);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		result[i] = ft_strdup(map[i]);
		if (!result[i])
		{
			while (i >= 0)
			{
				free(result[i]);
				i--;
			}
			free(result);
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}
