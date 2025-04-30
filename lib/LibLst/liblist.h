/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:55:30 by Evan              #+#    #+#             */
/*   Updated: 2025/03/04 16:55:33 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLIST_H
# define LIBLIST_H

# include "../LibMalloc/ft_malloc.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_front(t_list **lst, t_list *new_elem);
void				ft_lstadd_back(t_list **lst, t_list *new_elem);
void				ft_lstremove(t_list **lst, void *content, int (*cmp)(void *,
							void *));

void				ft_lstswap(t_list *a, t_list *b);
t_list				*ft_lstfind(t_list *lst, void *content, int (*cmp)(void *,
							void *));
int					ft_lstcount_if(t_list *lst, int (*f)(void *));

#endif
