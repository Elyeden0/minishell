/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_completion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:51:34 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:53:41 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_unique_str(t_list **lst, char *s)
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		if (ft_strcmp(cur->content, s) == 0)
			return ;
		cur = cur->next;
	}
	ft_lstadd_back(lst, ft_lstnew(s));
}

char	**ft_list_to_array(t_list *lst)
{
	int		len;
	char	**arr;
	int		i;

	len = ft_lstsize(lst);
	arr = ft_malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (lst)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	match_prefix(const char *s, const char *prefix)
{
	return (ft_strncmp(s, prefix, ft_strlen(prefix)) == 0);
}

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;
	char		ch;

	ch = (char)c;
	last = 0;
	while (*s)
	{
		if (*s == ch)
			last = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)last);
}

int	is_dir(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}
