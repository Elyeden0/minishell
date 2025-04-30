/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_modifications.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:23 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 17:43:32 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstremove(t_list **lst, void *content, int (*cmp)(void *, void *))
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !*lst || !cmp)
		return ;
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (cmp(current->content, content) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
			return ;
		}
		prev = current;
		current = current->next;
	}
}
