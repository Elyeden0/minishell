/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:19 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:55:22 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	void	*temp;

	if (!a || !b)
		return ;
	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

t_list	*ft_lstfind(t_list *lst, void *content, int (*cmp)(void *, void *))
{
	t_list	*current;

	if (!lst || !cmp)
		return (NULL);
	current = lst;
	while (current)
	{
		if (cmp(current->content, content) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_lstcount_if(t_list *lst, int (*f)(void *))
{
	int		count;
	t_list	*current;

	count = 0;
	current = lst;
	while (current)
	{
		if (f(current->content))
			count++;
		current = current->next;
	}
	return (count);
}
