/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:56:03 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 23:15:25 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

char	*ft_sigint_reset(const struct termios *orig, char **bp)
{
	(void)(*bp);
	g_signal = 0;
	ft_restore_termios(orig);
	return (ft_strdup(""));
}

char	*ft_eof_reset(const struct termios *orig, char *buf)
{
	(void)(buf);
	ft_restore_termios(orig);
	write(1, "\n", 1);
	return (NULL);
}
