/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:20:23 by Evan              #+#    #+#             */
/*   Updated: 2025/05/01 23:46:18 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signal_error(int sig)
{
	if (sig == SIGSEGV)
		printf("Segmentation fault");
	else if (sig == SIGABRT)
		printf("Aborted");
	else if (sig == SIGFPE)
		printf("Floating point exception");
	else if (sig == SIGBUS)
		printf("Bus error");
	else if (sig == SIGILL)
		printf("Illegal instruction");
	else
		printf("Terminated by signal %d", sig);
	printf(" (core dumped)\n");
}

void	handle_empty_command(void)
{
	char	buf[4096];
	ssize_t	n;

	if (!isatty(STDOUT_FILENO))
	{
		n = read(STDIN_FILENO, buf, sizeof(buf));
		while (n > 0)
		{
			write(STDOUT_FILENO, buf, n);
			n = read(STDIN_FILENO, buf, sizeof(buf));
		}
	}
	exit(0);
}
