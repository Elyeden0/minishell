/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:10:47 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 03:13:37 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_subshell(t_ast *child, t_env **env, int last_status)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (!pid)
		exit(exec_ast(child, env, last_status));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static int	exec_control_node(t_ast *node, t_env **env, int last_status)
{
	int	status;

	if (node->type == AST_AND)
	{
		status = exec_ast(node->left, env, last_status);
		if (!status)
			status = exec_ast(node->right, env, last_status);
	}
	else if (node->type == AST_OR)
	{
		status = exec_ast(node->left, env, last_status);
		if (status)
			status = exec_ast(node->right, env, last_status);
	}
	else if (node->type == AST_SEMI)
	{
		exec_ast(node->left, env, last_status);
		status = exec_ast(node->right, env, last_status);
	}
	else
		status = exec_subshell(node->child, env, last_status);
	return (status);
}

int	exec_ast(t_ast *node, t_env **env, int last_status)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == AST_CMD)
		status = exec_cmd(node, env, last_status);
	else if (node->type == AST_PIPE)
		status = exec_pipeline(node, env, last_status);
	else
		status = exec_control_node(node, env, last_status);
	return (status);
}
