/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:03:04 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 14:17:16 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_and_or(t_lexer *lx)
{
	char	c;

	c = lexer_peek(lx);
	if (c == '&' && lx->input[lx->pos + 1] == '&')
	{
		lexer_add_token(lx, T_AND_IF, NULL);
		lx->pos += 2;
		return (1);
	}
	if (c == '|' && lx->input[lx->pos + 1] == '|')
	{
		lexer_add_token(lx, T_OR_IF, NULL);
		lx->pos += 2;
		return (1);
	}
	return (0);
}

static int	handle_paren(t_lexer *lx)
{
	char	c;

	c = lexer_peek(lx);
	if (c == '(')
		lexer_add_token(lx, T_LPAREN, NULL);
	else
		lexer_add_token(lx, T_RPAREN, NULL);
	lexer_advance(lx);
	return (1);
}

int	handle_single_char(t_lexer *lx)
{
	char	c;

	c = lexer_peek(lx);
	if (c == '|')
	{
		lexer_add_token(lx, T_PIPE, NULL);
		lexer_advance(lx);
		return (1);
	}
	if (c == ';')
	{
		lexer_add_token(lx, T_SEMI, NULL);
		lexer_advance(lx);
		return (1);
	}
	if (c == '(' || c == ')')
		return (handle_paren(lx));
	return (0);
}

int	handle_redirection(t_lexer *lx)
{
	if (process_redirection_char(lx, '<', T_REDIR_IN, T_HEREDOC))
		return (1);
	if (process_redirection_char(lx, '>', T_REDIR_OUT, T_APPEND))
		return (1);
	return (0);
}

void	handle_word(t_lexer *lx)
{
	char	*buf;
	size_t	cap;
	size_t	i;
	char	c;

	cap = ft_strlen(lx->input + lx->pos) + 1;
	buf = ft_malloc(cap);
	if (!buf)
		return ;
	i = 0;
	c = lexer_peek(lx);
	while (c)
	{
		if (c == '\'' || c == '"')
			handle_quote(lx, buf, &i, c);
		else if (isspace((unsigned char)c) || is_op_char(c))
			break ;
		else
			handle_regular_char(lx, buf, &i);
		c = lexer_peek(lx);
	}
	buf[i] = '\0';
	lexer_add_token(lx, T_WORD, buf);
}
