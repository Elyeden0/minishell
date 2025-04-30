/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_buidlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:08:20 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 10:34:39 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*redir_new(t_token_type type, const char *target)
{
	t_redir	*r;

	r = ft_malloc(sizeof(*r));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = ft_strdup(target);
	r->next = NULL;
	return (r);
}

t_ast	*ast_new_cmd(char **argv, t_redir *redirs)
{
	t_ast	*n;

	n = ft_malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->type = AST_CMD;
	n->argv = argv;
	n->redirs = redirs;
	n->left = NULL;
	n->right = NULL;
	n->child = NULL;
	return (n);
}

t_ast	*ast_new_binary(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*n;

	n = ft_malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->type = type;
	n->argv = NULL;
	n->redirs = NULL;
	n->left = left;
	n->right = right;
	n->child = NULL;
	return (n);
}

t_ast	*ast_new_subshell(t_ast *child)
{
	t_ast	*n;

	n = ft_malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->type = AST_SUBSHELL;
	n->argv = NULL;
	n->redirs = NULL;
	n->left = NULL;
	n->right = NULL;
	n->child = child;
	return (n);
}
