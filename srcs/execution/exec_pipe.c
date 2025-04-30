/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:13:50 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 03:14:01 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_left_process(t_ast *node, t_env **env, int last_status,
		int *pipefd)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(exec_ast(node->left, env, last_status));
}

static void	run_right_process(t_ast *node, t_env **env, int last_status,
		int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	exit(exec_ast(node->right, env, last_status));
}

int	exec_pipeline(t_ast *node, t_env **env, int last_status)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	pipe(pipefd);
	pid_left = fork();
	if (!pid_left)
		run_left_process(node, env, last_status, pipefd);
	pid_right = fork();
	if (!pid_right)
		run_right_process(node, env, last_status, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	return (WEXITSTATUS(status_right));
}
