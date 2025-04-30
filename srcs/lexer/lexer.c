/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:43:40 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 14:14:43 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(t_lexer *lx, char *buf, size_t *i, char quote)
{
	char	c;

	lx->pos++;
	c = lexer_peek(lx);
	while (c && c != quote)
	{
		buf[*i] = c;
		(*i)++;
		lx->pos++;
		c = lexer_peek(lx);
	}
	if (lexer_peek(lx) == quote)
		lx->pos++;
}

t_lexer	*lexer_init(char *line)
{
	t_lexer	*lx;

	lx = ft_malloc(sizeof(*lx));
	if (!lx)
		return (NULL);
	lx->input = line;
	lx->pos = 0;
	lx->head = NULL;
	lx->tail = NULL;
	return (lx);
}

void	lexer_add_token(t_lexer *lx, t_token_type type, char *value)
{
	t_token	*tok;

	tok = ft_malloc(sizeof(*tok));
	if (!tok)
		return ;
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	if (!lx->head)
		lx->head = tok;
	else
		lx->tail->next = tok;
	lx->tail = tok;
}

int	process_redirection_char(t_lexer *lx, char c, t_token_type single,
		t_token_type dbl)
{
	if (lexer_peek(lx) != c)
		return (0);
	if (lx->input[lx->pos + 1] == c)
	{
		lexer_add_token(lx, dbl, NULL);
		lx->pos += 2;
	}
	else
	{
		lexer_add_token(lx, single, NULL);
		lexer_advance(lx);
	}
	return (1);
}

void	tokenize(t_lexer *lx)
{
	while (lexer_peek(lx))
	{
		if (isspace(lexer_peek(lx)))
			skip_whitespace(lx);
		else if (handle_and_or(lx))
			;
		else if (handle_single_char(lx))
			;
		else if (handle_redirection(lx))
			;
		else
			handle_word(lx);
	}
	lexer_add_token(lx, T_EOL, NULL);
}
