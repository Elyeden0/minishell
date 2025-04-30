/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:35:02 by Evan              #+#    #+#             */
/*   Updated: 2025/04/30 03:51:51 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static int	read_heredoc_lines(int fd, const char *delimiter)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = ft_readline("heredoc> ");
		count++;
		if (g_signal == SIGINT || !line)
		{
			printf("minishell: warning: here-document at line ");
			printf("%d delimited by end-of-file (wanted `%s')\n", count,
				delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (count);
}

void	redir_heredoc(const char *delimiter)
{
	int					hd[2];
	struct sigaction	hd_sa;
	struct sigaction	old_sa;

	if (pipe(hd) == -1)
		exit(1);
	ft_memset(&hd_sa, 0, sizeof(hd_sa));
	hd_sa.sa_handler = hd_sigint_handler;
	sigemptyset(&hd_sa.sa_mask);
	sigaction(SIGINT, &hd_sa, &old_sa);
	read_heredoc_lines(hd[1], delimiter);
	sigaction(SIGINT, &old_sa, NULL);
	g_signal = 0;
	close(hd[1]);
	dup2(hd[0], STDIN_FILENO);
	close(hd[0]);
}
