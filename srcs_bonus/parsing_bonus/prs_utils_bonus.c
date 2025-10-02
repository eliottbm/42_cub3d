/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:08:06 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/25 16:24:28 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

int	is_wall(char c)
{
	if (c == ' ' || c == '1' || c == '2')
		return (1);
	return (0);
}

int	check_ext(char *file, char *ext)
{
	int	len;

	len = ft_strlen(file);
	while (len > 1 && file[len - 1] && file[len - 1] != '.')
		len--;
	if (ft_ultimate_compare(&file[len - 1], ext) != 0)
		return (1);
	return (0);
}

int	isline_valid(char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if ((line[i] && line[i] != ' ') && (i == 0 || line[i - 1] == ' '))
			check += 1;
		i++;
	}
	if (check > 1)
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
