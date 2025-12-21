/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_doors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:18:00 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:45 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

t_doors	*d_lstnew(void *img, size_t n)
{
	t_doors	*elem;

	elem = malloc(sizeof(t_doors));
	if (!elem)
		return (NULL);
	elem->n = n;
	elem->img = img;
	elem->next = NULL;
	return (elem);
}

void	d_lstadd_sort(t_doors **lst, t_doors *new)
{
	t_doors	*node;

	if (!(*lst))
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	node = *lst;
	if (new->n < node->n)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		while (node->next && node->next->n < new->n)
			node = node->next;
		new->next = node->next;
		node->next = new;
	}
}

int	d_lstsize(t_doors *lst)
{
	int		i;
	t_doors	*current;

	if (!lst)
		return (0);
	i = 1;
	current = lst;
	while (current->next)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	d_lstorder_check(t_doors *doors)
{
	size_t	i;

	i = 1;
	while (doors)
	{
		if (doors->n != i)
			return (1);
		doors = doors->next;
		i++;
	}
	if (i == 1)
		return (1);
	return (0);
}

void	*get_ndoor_img(t_doors *lst, size_t	n)
{
	while (lst && lst->n != n)
		lst = lst->next;
	if (lst->n != n)
		return (NULL);
	return (lst->img);
}
