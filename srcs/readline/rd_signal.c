/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:55:42 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 22:55:42 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "^C\n", 3);
}

void	ft_sigquit_handler(int sig)
{
	(void)sig;
}

void	ft_setup_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ft_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = ft_sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}
