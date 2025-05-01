/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:03:48 by Evan              #+#    #+#             */
/*   Updated: 2025/05/01 12:16:18 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_input(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redir_output(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redir_append(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == T_REDIR_IN)
		{
			if (redirs->heredoc_fd >= 0)
			{
				dup2(redirs->heredoc_fd, STDIN_FILENO);
				close(redirs->heredoc_fd);
			}
			else
			{
				redir_input(redirs->target);
			}
		}
		else if (redirs->type == T_REDIR_OUT)
		{
			redir_output(redirs->target);
		}
		else if (redirs->type == T_APPEND)
		{
			redir_append(redirs->target);
		}
		redirs = redirs->next;
	}
}
