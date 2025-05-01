/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:20:23 by Evan              #+#    #+#             */
/*   Updated: 2025/05/01 12:22:55 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
