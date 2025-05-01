/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:35:02 by Evan              #+#    #+#             */
/*   Updated: 2025/05/02 00:12:40 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc_loop(int write_fd, const char *delimiter, t_env *env)
{
	char	*line;
	int		line_count;

	line_count = 1;
	while (1)
	{
		line = ft_readline("heredoc> ", env);
		if (!line)
		{
			printf("minishell: warning: here-document at line %d ", line_count);
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		line_count++;
	}
}

static void	process_single_heredoc(t_redir *r, t_env *env)
{
	int	hd[2];

	if (pipe(hd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	read_heredoc_loop(hd[1], r->target, env);
	close(hd[1]);
	r->target = NULL;
	r->type = T_REDIR_IN;
	r->heredoc_fd = hd[0];
}

static void	handle_cmd_heredocs(t_ast *node, t_env *env)
{
	t_redir	*r;

	r = node->redirs;
	while (r)
	{
		if (r->type == T_HEREDOC)
			process_single_heredoc(r, env);
		r = r->next;
	}
}

void	collect_heredocs(t_ast *node, t_env *env)
{
	if (!node)
		return ;
	if (node->type == AST_CMD)
		handle_cmd_heredocs(node, env);
	collect_heredocs(node->left, env);
	collect_heredocs(node->right, env);
	collect_heredocs(node->child, env);
}
