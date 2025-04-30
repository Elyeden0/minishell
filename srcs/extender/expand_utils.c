/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:52:40 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 19:14:14 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

char	*get_env_value(t_env *env, const char *key)
{
	size_t	keylen;

	keylen = ft_strlen(key);
	while (env)
	{
		if (env->data && ft_strncmp(env->data, key, keylen) == 0
			&& env->data[keylen] == '=')
			return (env->data + keylen + 1);
		env = env->next;
	}
	return ("");
}

char	*append_str(const char *dest, const char *src)
{
	size_t	l1;
	size_t	l2;
	char	*out;

	l1 = ft_strlen(dest);
	l2 = ft_strlen(src);
	out = ft_malloc(l1 + l2 + 1);
	ft_memcpy(out, dest, l1);
	ft_memcpy(out + l1, src, l2);
	out[l1 + l2] = '\0';
	return (out);
}

char	*itoa_status(int n)
{
	int		tmp;
	int		digits;
	char	*s;

	tmp = n;
	digits = (n <= 0);
	while (tmp > 0)
	{
		tmp /= 10;
		digits++;
	}
	s = ft_malloc(digits + 1);
	s[digits] = '\0';
	if (n == 0)
		s[0] = '0';
	while (n > 0)
	{
		s[--digits] = '0' + (n % 10);
		n /= 10;
	}
	return (s);
}

void	handle_single(t_expander *ex)
{
	int	start;

	ex->i++;
	start = ex->i;
	while (ex->s[ex->i] && ex->s[ex->i] != '\'')
		ex->i++;
	ex->res = append_str(ex->res, ft_strndup(ex->s + start, ex->i - start));
	if (ex->s[ex->i] == '\'')
		ex->i++;
}
