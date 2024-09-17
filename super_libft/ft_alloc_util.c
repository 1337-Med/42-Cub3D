/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:12:19 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/09/17 11:40:50 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_alloc_add_back(t_address **lst, t_address *new_node)
{
	t_address	*tmp;

	tmp = (*lst);
	if (!lst)
		return ;
	if (!(*lst))
		*lst = new_node;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

t_address	*ft_alloc_new_node(void *ptr, size_t size)
{
	t_address	*node;

	node = malloc(sizeof(t_address));
	if (!node)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
		return (NULL);
	}
	node->address = ptr;
	node->size = size;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
