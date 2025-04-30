/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:57:17 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 18:28:47 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

t_token_type	next_token(const char *l, int *i)
{
	skip_spaces(l, i);
	if (!l[*i])
		return (T_EOL);
	if (l[*i] == '\'' || l[*i] == '"')
	{
		if (skip_quotes(l, i))
			return (T_EOL);
		return (T_WORD);
	}
	if (ft_strchr("|&;<>()", l[*i]))
		return (get_operator(l, i));
	while (l[*i] && !isspace((unsigned char)l[*i]) && !ft_strchr("|&;<>()",
			l[*i]))
	{
		if (l[*i] == '\'' || l[*i] == '"')
			break ;
		(*i)++;
	}
	return (T_WORD);
}

void	lex_line(const char *l, t_token_type t[], int *c)
{
	int				i;
	t_token_type	tok;

	i = 0;
	*c = 0;
	while (1)
	{
		tok = next_token(l, &i);
		if (tok == T_EOL)
			break ;
		t[(*c)++] = tok;
	}
}
