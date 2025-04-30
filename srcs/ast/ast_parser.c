/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:07:44 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:34:51 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_ast(t_lexer *lexer)
{
	t_token	*cur;

	cur = lexer->head;
	return (parse_list(&cur));
}

t_ast	*parse_list(t_token **cur)
{
	t_ast	*node;
	t_ast	*rhs;

	node = parse_and_or(cur);
	while (peek_type(*cur) == T_SEMI)
	{
		consume_token(T_SEMI, cur);
		rhs = parse_and_or(cur);
		node = ast_new_binary(AST_SEMI, node, rhs);
	}
	return (node);
}

t_ast	*parse_and_or(t_token **cur)
{
	t_ast			*node;
	t_token_type	op;
	t_ast			*rhs;
	t_ast_type		type;

	node = parse_pipeline(cur);
	while (peek_type(*cur) == T_AND_IF || peek_type(*cur) == T_OR_IF)
	{
		op = peek_type(*cur);
		consume_token(op, cur);
		rhs = parse_pipeline(cur);
		if (op == T_AND_IF)
			type = AST_AND;
		else
			type = AST_OR;
		node = ast_new_binary(type, node, rhs);
	}
	return (node);
}

t_ast	*parse_pipeline(t_token **cur)
{
	t_ast	*node;
	t_ast	*rhs;

	node = parse_simple_cmd(cur);
	while (peek_type(*cur) == T_PIPE)
	{
		consume_token(T_PIPE, cur);
		rhs = parse_simple_cmd(cur);
		node = ast_new_binary(AST_PIPE, node, rhs);
	}
	return (node);
}

t_ast	*parse_simple_cmd(t_token **cur)
{
	t_ast	*sub;
	char	**argv;
	t_redir	*redir;

	if (peek_type(*cur) == T_LPAREN)
	{
		consume_token(T_LPAREN, cur);
		sub = parse_list(cur);
		if (!consume_token(T_RPAREN, cur))
			return (NULL);
		return (ast_new_subshell(sub));
	}
	argv = collect_arguments(cur);
	redir = collect_redirections(cur);
	return (ast_new_cmd(argv, redir));
}
