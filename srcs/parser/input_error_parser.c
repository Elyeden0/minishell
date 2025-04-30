/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:57:20 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 00:01:25 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_redir_double(const char *l, int *i)
{
	if (l[*i] == '<' && l[*i + 1] == '<')
	{
		*i += 2;
		return (T_HEREDOC);
	}
	if (l[*i] == '>' && l[*i + 1] == '>')
	{
		*i += 2;
		return (T_APPEND);
	}
	return (T_WORD);
}

t_token_type	get_logic_double(const char *l, int *i)
{
	if (l[*i] == '|' && l[*i + 1] == '|')
	{
		*i += 2;
		return (T_OR_IF);
	}
	if (l[*i] == '&' && l[*i + 1] == '&')
	{
		*i += 2;
		return (T_AND_IF);
	}
	if (l[*i] == '(')
	{
		(*i)++;
		return (T_LPAREN);
	}
	if (l[*i] == ')')
	{
		(*i)++;
		return (T_RPAREN);
	}
	return (T_WORD);
}

t_token_type	get_double_op(const char *l, int *i)
{
	t_token_type	tok;

	tok = get_redir_double(l, i);
	if (tok != T_WORD)
		return (tok);
	return (get_logic_double(l, i));
}

t_token_type	get_single_op(const char *l, int *i)
{
	if (l[*i] == '|')
	{
		(*i)++;
		return (T_PIPE);
	}
	if (l[*i] == ';')
	{
		(*i)++;
		return (T_SEMI);
	}
	if (l[*i] == '<')
	{
		(*i)++;
		return (T_REDIR_IN);
	}
	if (l[*i] == '>')
	{
		(*i)++;
		return (T_REDIR_OUT);
	}
	return (T_WORD);
}

t_token_type	get_operator(const char *l, int *i)
{
	t_token_type	tok;

	tok = get_double_op(l, i);
	if (tok != T_WORD)
		return (tok);
	return (get_single_op(l, i));
}
