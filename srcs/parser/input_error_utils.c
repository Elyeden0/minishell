/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:57:23 by Evan              #+#    #+#             */
/*   Updated: 2025/04/29 18:28:07 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_to_str(t_token_type type)
{
	if (type == T_PIPE)
		return ("|");
	if (type == T_AND_IF)
		return ("&&");
	if (type == T_OR_IF)
		return ("||");
	if (type == T_SEMI)
		return (";");
	if (type == T_REDIR_IN)
		return ("<");
	if (type == T_HEREDOC)
		return ("<<");
	if (type == T_REDIR_OUT)
		return (">");
	if (type == T_APPEND)
		return (">>");
	if (type == T_LPAREN)
		return ("(");
	if (type == T_RPAREN)
		return (")");
	return ("newline");
}

void	report(char *s)
{
	printf("minishell: syntax error near unexpected token `%s'\n", s);
}

void	skip_spaces(const char *l, int *i)
{
	while (l[*i] && isspace((unsigned char)l[*i]))
		(*i)++;
}

int	skip_quotes(const char *l, int *i)
{
	char	q;

	q = l[*i];
	(*i)++;
	while (l[*i] && l[*i] != q)
		(*i)++;
	if (l[*i] == q)
	{
		(*i)++;
		return (0);
	}
	printf("minishell: syntax error: missing closing %c\n", q);
	return (1);
}
