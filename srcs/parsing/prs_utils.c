/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:08:06 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/08 14:54:36 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	is_wall(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}

int	tab_iscolor(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > 3)
			return (0);
		if (!ft_strisdigit(tab[i]))
			return (0);
		if (ft_atoi(tab[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}

int	isline_valid(char *line, int ntex)
{
	size_t	i;
	int		check;
	char	lc;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (ntex >= 4 && line[i + 1]
			&& line[i + 1] == ' ' && line[i] != ' ')
			lc = line[i];
		else if (ntex >= 4 && i > 0
			&& line[i - 1] == ' ' && line[i] != ' '
			&& ((ft_isdigit(lc) && ft_isdigit(line[i]))
				|| (!ft_isdigit(lc) && !ft_isdigit(line[i]))))
			return (1);
		if ((line[i] && line[i] != ' ') && (i == 0 || line[i - 1] == ' '))
			check += 1;
		i++;
	}
	if (ntex < 4 && check > 1)
		return (1);
	return (0);
}

static size_t	ft_strlenset(char *str, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
}

char	*strrmset(char *str, char c)
{
	char	*newstr;
	size_t	nset;
	size_t	i;
	size_t	j;

	nset = ft_strlenset(str, c);
	newstr = malloc(sizeof(char) * (ft_strlen(str) - nset + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	return (newstr);
}
