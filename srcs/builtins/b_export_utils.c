/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:57:33 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 02:25:27 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

size_t	strlen_equal(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || (!is_alpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*res;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = ft_malloc(l1 + l2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, l1);
	ft_memcpy(res + l1, s2, l2);
	res[l1 + l2] = '\0';
	return (res);
}

void	link_new_env(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (!*env)
		*env = node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
