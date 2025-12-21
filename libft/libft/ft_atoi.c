/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:33:47 by mtrullar          #+#    #+#             */
/*   Updated: 2024/11/28 15:52:03 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	signe;
	long	result;

	i = 0;
	result = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += (nptr[i] - '0');
		i++;
	}
	return (signe * result);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		signe;
	int		result;

	i = 0;
	result = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += (nptr[i] - '0');
		i++;
	}
	return (signe * result);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	signe;
	long long	result;

	i = 0;
	result = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += (nptr[i] - '0');
		i++;
	}
	return (signe * result);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
