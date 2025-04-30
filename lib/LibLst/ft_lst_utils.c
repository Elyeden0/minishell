/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:26 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:55:28 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)ft_malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current;

	count = 0;
	current = lst;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}
