/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Evan <Evan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:56:01 by Evan              #+#    #+#             */
/*   Updated: 2025/04/27 22:56:02 by Evan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_termios(int *inited, struct termios *orig, struct termios *raw)
{
	if (*inited == 0)
	{
		ft_setup_signal();
		tcgetattr(STDIN_FILENO, orig);
		*raw = *orig;
		raw->c_lflag &= ~(ECHO | ICANON);
		raw->c_cc[VMIN] = 1;
		raw->c_cc[VTIME] = 0;
		*inited = 1;
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
}

void	ft_restore_termios(const struct termios *orig)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig);
}

void	ft_print_prompt(const char *prompt)
{
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
}
