/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_maps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:18:00 by ebengtss          #+#    #+#             */
/*   Updated: 2024/11/25 17:41:00 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs_bonus/cub3d_bonus.h"

t_maps	*m_lstnew(char *name, char *path)
{
	t_maps	*elem;

	elem = malloc(sizeof(t_maps));
	if (!elem)
		return (NULL);
	elem->name = name;
	elem->path = path;
	elem->preview = NULL;
	elem->next = NULL;
	return (elem);
}

void	m_lstadd_front(t_maps **lst, t_maps *new)
{
	new->next = *lst;
	*lst = new;
}

t_maps	*m_lstlast(t_maps *lst)
{
	t_maps	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	m_lstadd_back(t_maps **lst, t_maps *new)
{
	t_maps	*last;

	if (!(*lst))
		m_lstadd_front(lst, new);
	else
	{
		last = m_lstlast(*lst);
		last->next = new;
	}
}

int	m_lstsize(t_maps *lst)
{
	int		i;
	t_maps	*current;

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
