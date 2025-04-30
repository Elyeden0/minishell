/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:50:53 by Evan              #+#    #+#             */
/*   Updated: 2025/04/28 02:18:28 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd_op(t_token_type t)
{
	return (t == T_PIPE || t == T_AND_IF || t == T_OR_IF || t == T_SEMI);
}

int	handle_cmd_op_error(t_token_type t[], int j, int c)
{
	if (j == 0 || (t[j - 1] != T_WORD && t[j - 1] != T_RPAREN))
	{
		report((char *)token_to_str(t[j]));
		return (1);
	}
	if (j + 1 >= c)
	{
		report("newline");
		return (1);
	}
	if (is_cmd_op(t[j + 1]))
	{
		report((char *)token_to_str(t[j + 1]));
		return (1);
	}
	return (0);
}

int	check_cmd_ops(t_token_type t[], int c)
{
	int	j;

	j = 0;
	while (j < c)
	{
		if (is_cmd_op(t[j]))
			if (handle_cmd_op_error(t, j, c))
				return (1);
		j++;
	}
	return (0);
}

int	check_redir_ops(t_token_type t[], int c)
{
	int	j;

	j = 0;
	while (j < c)
	{
		if (t[j] == T_REDIR_IN || t[j] == T_HEREDOC || t[j] == T_REDIR_OUT
			|| t[j] == T_APPEND)
		{
			if (j + 1 >= c)
			{
				report("newline");
				return (1);
			}
			if (t[j + 1] != T_WORD)
			{
				report((char *)token_to_str(t[j + 1]));
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	syntax_error(const char *line)
{
	t_token_type	tokens[1024];
	int				count;

	lex_line(line, tokens, &count);
	if (check_cmd_ops(tokens, count))
		return (1);
	if (check_paren_ops(tokens, count))
		return (1);
	if (check_redir_ops(tokens, count))
		return (1);
	return (0);
}
