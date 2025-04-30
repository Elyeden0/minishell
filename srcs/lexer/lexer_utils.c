/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:03:18 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 02:18:19 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = ft_malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_op_char(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

char	lexer_peek(t_lexer *lx)
{
	return (lx->input[lx->pos]);
}

void	lexer_advance(t_lexer *lx)
{
	if (lx->input[lx->pos])
		lx->pos++;
}

void	skip_whitespace(t_lexer *lx)
{
	while (isspace(lexer_peek(lx)))
		lexer_advance(lx);
}
